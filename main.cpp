#include"1.h"

int main(int argsv,char const *s[])
{
    FILE *fp1;
    fp1 = fopen(*(s+4),"w");
    double A[4],B[4];
    input(A,B,s);
    
    vertex *v = NULL;
    v = new vertex();
    v->setnextvertex(NULL);
    vertex_data_set(A,B,v);

    Halfedges *ho = NULL;
    ho = new Halfedges();
    ho -> setstartvertex(NULL);
    ho -> setendvertex(NULL);
    ho -> setnexthalfedge( NULL);
    ho -> setprevhalfedge(   NULL);
    


    Halfedges *hi = NULL;
    hi = new Halfedges();
    hi -> setstartvertex(NULL);
    hi -> setendvertex(NULL);
    hi -> setnexthalfedge(NULL);
    hi -> setprevhalfedge(NULL);
    makeouter(v,hi);
    makeinner(v,ho);

    
    vector<edge*> edgev;
    edge *e = NULL;
    e = new edge();
    e -> setnextedge(NULL);
    e -> setprevedge(NULL);
    e -> setouterhalfedge(NULL);
    e -> setinnerhalfedge(NULL);
    input_set(v,e,ho,hi,edgev);

    face *f = NULL;
    f = new face();
    f -> setedgesin(e);
    f -> setnextface(NULL);
    f -> setprevface(NULL);
    f -> sethalfedgesin(e->getinnerhalfedge());
    
    setfaces(ho,hi,f);
    

    int s1_1[100],s2_1[100];
    int na =1;
    na = input_1(s1_1,s2_1,s);
   
   
    int s1[na],s2[na];

    for(int i = 0;i<na;i++)
    {
        s1[i] = s1_1[i];
        s2[i] = s2_1[i];
    }

    int noe = 4;
    int nov = 4;
    for(int i = 0;i<na;i++)
    {
       
        fprintf(fp1,"after %d splits",i);
        output_k(v,ho,hi,e,f,noe,edgev,fp1);
        split(v,ho,hi,e,f,s1[i],s2[i],edgev,noe,nov);
        noe += 3;
        nov += 2;
    }
    
    output_k(v,ho,hi,e,f,noe,edgev,fp1);
    
    fprintf(fp1,"\n\n\n\nAfter IDS: \n");

    double P[100],Q[100];
    int na1 = 1;
    na1 = input_2(P,Q,s);


    for(int i = 0;i<na1 ;i++)
    {
    	fprintf(fp1,"For id %d : Faceindex = %d\n",i+1,find_face_in(f,P[i],Q[i]));
    }

    fclose(fp1);
    return 0;
}
