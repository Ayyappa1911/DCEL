#include"1.h"

void input(double *arr1,double *arr2,char const *s[])
{
	FILE *fp;
	fp = fopen(*(s+1),"rb");
	extract_data(arr1,arr2,fp);
	fclose(fp);
	return;
}
void extract_data(double *arr1,double *arr2,FILE *fp)
{
	int flag = 1;
	int i = 0;
	int o = 0;
	unsigned char temp = 0;
	double a,b;
	for(int q = 0 ; q< 4;q++)
	{
		fscanf(fp,"%lf %lf",&a,&b);
		*(arr1+q) = a;
		*(arr2+q) = b;
	}
	return;
}

int input_1(int *arr1,int *arr2,char const *s[])
{
	FILE *fp;
	fp = fopen(*(s+2),"rb");
	int p = extract_data_1(arr1,arr2,fp);
	fclose(fp);
	return p;
}
int extract_data_1(int *arr1,int *arr2,FILE *fp)
{
	int flag = 1;
	int i = 0;
	int o = 0;
	unsigned char temp ;
    	char arr[50];
	int a,b;
    	int arrk[100],arrl[100];
	while ((fp!=NULL))
    	{
		fscanf(fp,"%d %d",&a,&b);
		*(arr1+o) = a;
		*(arr2+o) = b;
        	int arrk[100];
        	int arrl[100]; 
        	arrk[o] = a;
        	arrl[o] = b;
        	if(arrk[o-1] == a && arrl[o-1] == b)
        	{
            		break;
        	}
        	o++;
	}
	return o;
}

int input_2(double *arr1,double *arr2,char const *s[])
{
	FILE *fp;
	fp = fopen(*(s+3),"rb");
	int p = extract_data_2(arr1,arr2,fp);
	fclose(fp);
	return p;
}
int extract_data_2(double *arr1,double *arr2,FILE *fp)
{
	int flag = 1;
	int i = 0;
	int o = 0;
	unsigned char temp ;
    	char arr[50];
	double a,b;
    	double arrk[100],arrl[100];
	while ((fp!=NULL))
    	{
		fscanf(fp,"%lf %lf",&a,&b);
		*(arr1+o) = a;
		*(arr2+o) = b;
        	double arrk[100];
        	double arrl[100]; 
        	arrk[o] = a;
        	arrl[o] = b;
        	if(arrk[o-1] == a && arrl[o-1] == b)
        	{
            		break;
        	}
        	o++;
	}
	return o;
}


int find_face_in(face *f,double x,double y)
{
    face *temp = f;
    int faceindex ;
    while(temp!=NULL)
    {
        double a,b;
        centroid(temp,&a,&b);
        int flag = 0;
        flag = is_it_in_face(temp,a,b,x,y);
        if(flag == 1)
        {
            faceindex = temp -> getfaceindex();
            break;
        }
        temp = temp -> getnextface();
    }
    
    return faceindex;
}
void centroid(face *f,double *a,double *b)
{
    Halfedges *h = (f->gethalfedgesin());
    Halfedges *h1 = h;
    double x =0 ;
    double y = 0;
    int index  =0;
    do
    {
        x += (h -> getstartvertex()) -> getx();
        y += (h -> getstartvertex()) -> gety();
        index ++;
        h = h -> getnexthalfedge();
    } while (h != h1);
    *a = x/index;
    *b = y/index;
    return;
}
int is_it_in_face(face *temp,double a,double b,double x,double y)
{
    Halfedges *h = (temp->gethalfedgesin());
    Halfedges *h1 = h;
    int flag = 1;
    do
    {
        if(is_sign_not_same(a,b,x,y,h))
        {
            flag = 0;
            break;
        }
        h = h -> getnexthalfedge();
    } while (h != h1);

    return flag;
}
int is_sign_not_same(double a,double b,double x,double y,Halfedges *h)
{
    double x1,x2,y1,y2;
    x1 = (h->getstartvertex())->getx();
    x2 = (h->getendvertex())->getx();
    y1 = (h->getstartvertex())->gety();
    y2 = (h->getendvertex())->gety();
    double m ;
    m = y2-y1;
    m = m /(x2-x1);
    double a1 = (b - y1) - m*(a-x1);
    double b1 = (y - y1) - m*(x -x1);
    if(a1*b1 > 0)
    {
        return 0;
    }
    else if(a1*b1 <0)
    {
        return 1;
    }
    return 0;
}
void setfaces(Halfedges *ho,Halfedges *hi,face *f)
{
    Halfedges *tempho = ho;
    Halfedges *temphi = hi;
    do
    {
        tempho -> setfacein(NULL);
        tempho = tempho -> getnexthalfedge();
    }while(tempho!= ho);
    do
    {
        temphi -> setfacein(f);
        temphi = temphi -> getnexthalfedge();
    } while(temphi!=hi);
    return ;
}
void split(vertex *v,Halfedges *ho,Halfedges *hi,edge *e,face *f,double a,double b,vector<edge*> &edgev,int noe,int nov)
{
    edge *tempa = edgev[a];
    edge *tempb = edgev[b];

    face *fk = NULL;
    vertex *p1 = (tempa -> getinnerhalfedge()) -> getendvertex();
    vertex *p2 = (tempb -> getinnerhalfedge()) -> getstartvertex();

    int k1 = ((tempa -> getinnerhalfedge()) -> getfacein()) -> getfaceindex();
    int k2 = -555;
    if((tempa -> getouterhalfedge()) -> getfacein() != NULL)
    {
        k2 = ((tempa -> getouterhalfedge()) -> getfacein()) -> getfaceindex();
    }
    int k3 = ((tempb -> getinnerhalfedge()) -> getfacein()) -> getfaceindex();
    int k4 = -895;
    if((tempb -> getouterhalfedge()) -> getfacein() != NULL)
    {
        k4 = ((tempb -> getouterhalfedge()) -> getfacein()) -> getfaceindex();
    }
    if(k1 == k3 || k1 == k4)
    {
        fk = (tempa -> getinnerhalfedge()) -> getfacein();
    }
    else if(k2 == k3 || k2 == k4)
    {
       fk = (tempb -> getinnerhalfedge()) -> getfacein(); 
    }

    double x1 = ( ((tempa -> getinnerhalfedge()) -> getstartvertex()) -> getx() )  +   ( ((tempa -> getinnerhalfedge()) -> getendvertex()) -> getx() ) ;
    x1 = x1/2;
    double y1 = ( ((tempa -> getinnerhalfedge()) -> getstartvertex()) -> gety() )  +   ( ((tempa -> getinnerhalfedge()) -> getendvertex()) -> gety() ) ;
    y1 = y1/2;
    double x2 = ( ((tempb -> getinnerhalfedge()) -> getstartvertex()) -> getx() )  +   ( ((tempb -> getinnerhalfedge()) -> getendvertex()) -> getx() ) ;
    x2 = x2/2;
    double y2 = ( ((tempb -> getinnerhalfedge()) -> getstartvertex()) -> gety() )  +   ( ((tempb -> getinnerhalfedge()) -> getendvertex()) -> gety() ) ;
    y2 = y2/2;


    
    int flag = 0;
    if(tempa -> getnextedge() != tempb)
    {
        flag = 1;
    }

    edge *TA = tempa -> getnextedge();
    edge *TB = tempb -> getprevedge();

    vertex *v1 = NULL;
    v1 = new vertex();
    v1 -> setx(x1);
    v1 -> sety(y1);
    v1 -> setvertexindex(nov+0);
    v1 -> setprevvertex(tempa -> getverticesin());



    vertex *v2 = NULL;
    v2 = new vertex();
    v2 -> setx(x2);
    v2 -> sety(y2);
    v2 -> setvertexindex(nov+1);
    v2 -> setprevvertex(tempb -> getverticesin());
    
    vertex *va1= (tempa -> getverticesin()) -> getnextvertex();
    (tempa -> getverticesin()) -> setnextvertex(v1);
    v1 -> setnextvertex(va1);
    va1 -> setprevvertex(v1);

    (tempa -> getverticesin()) -> setnextvertex(v1);

    vertex *va2 = ((tempb -> getnextedge())->getverticesin());

    v2 -> setnextvertex(va2);
    va2 -> setprevvertex(v2);

    tempb -> setverticesin(v2);

    (tempb -> getouterhalfedge()) -> setendvertex(v2);
    

    edge *e1 = NULL;
    e1 = new edge();
    e1 -> setverticesin(v1);
    e1 -> setprevedge(tempa); 
    e1 -> setnextedge(tempb);
    e1 -> setinnerhalfedge(NULL);
    e1 -> setouterhalfedge(NULL);
    e1 -> setedgeindex(noe+0);

    edgev.push_back(e1);

    edge* tempa1 = NULL;
    tempa1 = new edge();
    tempa1 -> setverticesin(v1);
    tempa1 -> setprevedge(tempa);
    
    tempa1 -> setinnerhalfedge(NULL);
    tempa1 -> setouterhalfedge(NULL);
    tempa1 -> setedgeindex(noe+1);
    tempa -> setnextedge(tempa1);

    

    edge* tempb1 = NULL;
    tempb1 = new edge();
    tempb1 -> setverticesin(v2->getprevvertex());
    if(flag == 0)
    {
        tempb1 -> setprevedge(tempa1);
    }
    else if(flag == 1)
    {
        tempb1 -> setprevedge(TB);
    }
    tempb1 -> setnextedge(tempb);
    tempb1 -> setinnerhalfedge(NULL);
    tempb1 -> setouterhalfedge(NULL);
    tempb1 -> setedgeindex(noe+2);
    tempb -> setprevedge(tempb1);
    (tempb -> getinnerhalfedge()) -> setstartvertex(v2);

    edgev.push_back(tempa1);
    edgev.push_back(tempb1);
    
    if(flag == 0)
    {
        tempa1 -> setnextedge(tempb1);
    }
    else if(flag == 1)
    {
        tempa1 -> setnextedge(TA);
    }
    (tempa -> getinnerhalfedge()) -> setendvertex(v1);
    (tempa -> getouterhalfedge()) -> setstartvertex(v1);

    Halfedges *ha = NULL;
    ha = new Halfedges();
    ha -> setstartvertex(v1);
    ha -> setendvertex(v2);
    ha -> setnexthalfedge(tempb -> getinnerhalfedge());
    ha -> setprevhalfedge(tempa -> getinnerhalfedge());
    ha -> setedgeindexval(noe+0);
    ha -> setedgein(e1);

    Halfedges *hb = NULL;
    hb = new Halfedges();
    hb -> setstartvertex(v2);
    hb -> setendvertex(v1);
    hb -> setnexthalfedge(NULL);
    hb -> setprevhalfedge(NULL);
    hb -> setedgeindexval(noe+0);
    hb -> setedgein(e1);

    e1 -> setinnerhalfedge(ha);
    e1 -> setouterhalfedge(hb);

    Halfedges *htempa = NULL;
    htempa = new Halfedges();
    htempa -> setstartvertex(v1);
    htempa -> setendvertex((p1));
    htempa -> setnexthalfedge(NULL);
    htempa -> setprevhalfedge(hb);
    htempa -> setedgeindexval(noe+1);
    htempa -> setedgein(tempa1);


    Halfedges *htempa1 = NULL;
    htempa1 = new Halfedges();
    htempa1 -> setstartvertex(p1);
    htempa1 -> setendvertex(v1);
    htempa1 -> setnexthalfedge(tempa -> getouterhalfedge());
    Halfedges *U1= (tempa -> getouterhalfedge()) -> getprevhalfedge();
    (tempa -> getouterhalfedge()) -> setprevhalfedge(htempa1);
    U1 -> setnexthalfedge(htempa1);
    htempa1 -> setprevhalfedge(NULL);
    htempa1 -> setedgeindexval(noe+1);
    htempa1 -> setedgein(tempa1);

    tempa1->setinnerhalfedge(htempa);
    tempa1->setouterhalfedge(htempa1);

    Halfedges *htempb = NULL;
    htempb = new Halfedges();
    htempb -> setstartvertex(p2);
    htempb -> setendvertex(v2);
    htempb -> setnexthalfedge(hb);
    htempb -> setprevhalfedge(NULL);
    htempb -> setedgeindexval(noe+2);
    htempb -> setedgein(tempb1);


    Halfedges *htempb1 = NULL;
    htempb1 = new Halfedges();
    htempb1 -> setstartvertex(v2);
    htempb1 -> setendvertex(p2);
    htempb1 -> setnexthalfedge(NULL);
    htempb1 -> setprevhalfedge(tempb -> getouterhalfedge());
    Halfedges *U2 = (tempb -> getouterhalfedge()) -> getnexthalfedge();
    (tempb -> getouterhalfedge()) -> setnexthalfedge(htempb1);
    U2 -> setprevhalfedge(htempb1);
    htempb1 -> setedgeindexval(noe+2);
    htempb1 -> setedgein(tempb1);

    tempb1->setinnerhalfedge(htempb);
    tempb1->setouterhalfedge(htempb1);

    if(flag == 0)
    {
        htempa -> setnexthalfedge(htempb);
        htempa1 -> setprevhalfedge(htempb1);
        htempb -> setprevhalfedge(htempa);
        htempb1 -> setnexthalfedge(htempa1);

    }
    else if(flag == 1)
    {
        htempa -> setnexthalfedge((TA)->getinnerhalfedge());
        (TA -> getinnerhalfedge()) -> setprevhalfedge(htempa);
        htempa1 -> setprevhalfedge((TA)-> getouterhalfedge());
        (TA -> getouterhalfedge()) -> setnexthalfedge(htempa1);
        htempb -> setprevhalfedge((TB)->getouterhalfedge());
        (TB -> getinnerhalfedge()) -> setnexthalfedge(htempb);
        htempb1 -> setnexthalfedge(U2);
        (U2) -> setprevhalfedge(htempb1);
    }


    hb -> setnexthalfedge(htempa);
    hb -> setprevhalfedge(htempb);


    (tempa -> getinnerhalfedge())->setnexthalfedge(ha);
    (tempb -> getinnerhalfedge()) -> setprevhalfedge(ha);

    
    
    face *fa = f;
    int i = 0;
    while(fa -> getnextface() != NULL)
    {
        fa = fa -> getnextface();
        i++;
    }
    fk -> sethalfedgesin(e1 -> getinnerhalfedge());

    face *f1 = NULL;
    f1 = new face();
    f1 -> setfaceindex(i+1);
    f1 -> setedgesin(e1);                                    
    f1 -> setnextface(NULL);
    f1 -> setprevface(fa);
    fa -> setnextface(f1);
    f1 -> sethalfedgesin(e1 -> getouterhalfedge());


    fk -> setedgesin(e1); 
    fk -> sethalfedgesin(e1 -> getinnerhalfedge());   

    

    ha -> setfacein(f);
    hb -> setfacein(f1);
    htempa ->setfacein(f1);
    htempb -> setfacein(f1);
    htempa1->setfacein(NULL);
    htempb1->setfacein(NULL);

    if((htempa1 -> getnexthalfedge())-> getfacein() != NULL )  
    {
        htempa1 -> setfacein(((htempa1 -> getnexthalfedge())->getfacein()));
    }
    else if( (htempa1 -> getprevhalfedge())-> getfacein() != NULL ) 
    {
        htempa1 -> setfacein(((htempa1 -> getprevhalfedge())->getfacein()));
    }

    if((htempb1 -> getnexthalfedge())-> getfacein() != NULL )  
    {
        htempb1 -> setfacein(((htempb1 -> getnexthalfedge())->getfacein()));
    }
    else if( (htempb1 -> getprevhalfedge())-> getfacein() != NULL ) 
    {
        htempb1 -> setfacein(((htempb1 -> getprevhalfedge())->getfacein()));
    }
    
    
    
    
    Halfedges *hf1 = f1 -> gethalfedgesin();
    Halfedges *hf2 = f1 -> gethalfedgesin();
    do
    {
        hf1 -> setfacein(f1);
        hf1 = hf1 -> getnexthalfedge();
    }while(hf1!=hf2);
    
    return;
}
void makeinner(vertex *v,Halfedges *hi)
{
    vertex *temp1 = v->getnextvertex();
    hi -> setstartvertex(temp1);
    hi -> setendvertex(temp1->getprevvertex());
    temp1 = temp1 -> getprevvertex();
    Halfedges *temph = hi;
    for(int i = 1;i<4;i++)
    {
        Halfedges *temp = NULL;
        temp = new Halfedges();
        temp -> setstartvertex(temp1);
        temp -> setendvertex(temp1 -> getprevvertex());
        temp1 = temp1 -> getprevvertex();
        temph -> setnexthalfedge(temp);
        temp -> setprevhalfedge(temph);
        temph = temph -> getnexthalfedge();
    }
    hi -> setprevhalfedge(temph);
    temph -> setnexthalfedge(hi);
    return;
}
void makeouter(vertex* v,Halfedges* ho)
{
    vertex *temp1 = v;
    ho->setstartvertex(temp1);
    ho -> setendvertex(temp1->getnextvertex());
    temp1 = temp1 -> getnextvertex();
    Halfedges *temph = ho;
    for(int i=1;i<4;i++)
    {
        Halfedges *temp = NULL;
        temp = new Halfedges();
        temp -> setstartvertex(temp1);
        temp -> setendvertex(temp1->getnextvertex());
        temp1 = temp1 -> getnextvertex();
        temph -> setnexthalfedge(temp);
        temp ->setprevhalfedge(temph);
        temph = temph -> getnexthalfedge();
    }
    ho -> setprevhalfedge(temph);
    temph -> setnexthalfedge(ho);
    return ;
}
void input_set( vertex *v,edge *e,Halfedges *ho,Halfedges *hi,vector<edge*> &edgev)
{
    vertex *tempx = v;
    e -> setverticesin(tempx);
    tempx = tempx -> getnextvertex();
    e->setedgeindex(0);
    Halfedges *hi1 = hi;
    Halfedges *ho1 = ho;
    e->setinnerhalfedge(hi1);
    e->setouterhalfedge(ho1);
    hi1 -> setedgeindexval(0);
    ho -> setedgeindexval(0);
    edge *temp1 = e;
    edgev.push_back(temp1);
    hi1->setedgein(temp1);
    ho1->setedgein(temp1);
    hi1 = hi1 -> getnexthalfedge();
    ho1 = ho1 -> getprevhalfedge();
    for(int i = 1;i<4;i++)
    {
        edge *temp = NULL;
       
        temp = new edge();
        temp -> setverticesin(tempx);
        tempx = tempx -> getnextvertex();
        temp->setedgeindex(i);
        hi1 -> setedgeindexval(i);
        ho1 -> setedgeindexval(i);
        temp -> setinnerhalfedge(hi1);
        temp -> setouterhalfedge(ho1);
        hi1 -> setedgein(temp);
        ho1 -> setedgein(temp);
        hi1 = hi1 -> getnexthalfedge();
        ho1 = ho1 -> getprevhalfedge();
        temp -> setnextedge(NULL);
        temp1 -> setnextedge(temp);
        temp->setprevedge(temp1);
        temp1 = temp1->getnextedge();
        edgev.push_back(temp);
    }
    temp1 -> setnextedge(e);
    e ->setprevedge(temp1);
    edge *temp = NULL;
    temp = e;
}
void vertex_data_set(double *A,double *B,vertex *v)
{
    v->setx(*(A));
    v->sety(*(B));
    v->setvertexindex(0);
    vertex *temp1 = v;
    for(int i = 1;i<4;i++)
    {
        vertex *temp = NULL;
        temp = new vertex();
        temp -> setx(*(A+i));
        temp -> sety(*(B+i));
        temp -> setvertexindex(i);
        temp -> setnextvertex(NULL);
        temp1 -> setnextvertex(temp);
        temp -> setprevvertex(temp1);
        temp1 = temp1 -> getnextvertex();
    }
    v -> setprevvertex(temp1);
    temp1 -> setnextvertex(v);
    vertex *temp = NULL;
    temp = v;
    return;
}
void output_k(vertex *v,Halfedges *ho,Halfedges *hi,edge *e,face *f,int noe,vector<edge*> &edgev,FILE *fp1)
{
   
    fprintf(fp1,"Edges:\n");
    for(int i = 0;i<noe ; i++)
    {
      
      fprintf(fp1,"%d\n",edgev[i]->getedgeindex());
    }
    
    fprintf(fp1,"Halfedges:\n");
    for (int i = 0; i < noe; i++)
    {
        Halfedges *temph = (edgev[i])->getinnerhalfedge();
       
        fprintf(fp1,"startVertexIndex=");
        fprintf(fp1,"%d ",(temph -> getstartvertex())->getvertexindex());
        fprintf(fp1,"endVertexIndex=");
        fprintf(fp1,"%d ",((temph -> getendvertex()) -> getvertexindex()));
        fprintf(fp1,"nextEdge=");
        fprintf(fp1,"%d ",((temph -> getnexthalfedge())->getedgein()) -> getedgeindex());
        fprintf(fp1,"prevEdge=");
        fprintf(fp1,"%d ",((temph -> getprevhalfedge()) -> getedgein()) -> getedgeindex());
        fprintf(fp1,"faceIndex=");
        fprintf(fp1,"%d ",(temph->getfacein())->getfaceindex());
        fprintf(fp1,"edgeIndex=");
        fprintf(fp1,"%d\n",(temph->getedgein())->getedgeindex());

       
       Halfedges *temph1  = (edgev[i])->getouterhalfedge();
       if(temph1 -> getfacein() != NULL)
       {
           fprintf(fp1,"startVertexIndex=");
           fprintf(fp1,"%d ",(temph -> getstartvertex())->getvertexindex());
           fprintf(fp1,"endVertexIndex=");
           fprintf(fp1,"%d ",((temph -> getendvertex()) -> getvertexindex()));
           fprintf(fp1,"nextEdge=");
           fprintf(fp1,"%d ",((temph -> getnexthalfedge())->getedgein()) -> getedgeindex());
           fprintf(fp1,"prevEdge=");
           fprintf(fp1,"%d ",((temph -> getprevhalfedge()) -> getedgein()) -> getedgeindex());
           fprintf(fp1,"faceIndex=");
           fprintf(fp1,"%d ",(temph->getfacein())->getfaceindex());
           fprintf(fp1,"edgeIndex=");
           fprintf(fp1,"%d\n",(temph->getedgein())->getedgeindex());
         
       }
      
    }
 
    fprintf(fp1,"Faces:\n");
    face *tf = f;
    Halfedges *tempe = NULL;
    Halfedges *tempe1 = NULL;
   
    while(tf != NULL)
    {
        fprintf(fp1,"FaceIndex=");
        fprintf(fp1," %d ",tf->getfaceindex());
        
        tempe1 = tf->gethalfedgesin();
        tempe = tempe1; 
       
        do
        {
            fprintf(fp1,"%d",(tempe1 ->getedgein()) -> getedgeindex());
           
            if((tempe1->getnexthalfedge()) != (tempe))
            {
                fprintf(fp1,"->");
    
            }
            tempe1 = tempe1 -> getnexthalfedge();
           
        } while (tempe != tempe1);
     
        tf = tf -> getnextface();
       
        fprintf(fp1,"\n");
    }
    
    
}


