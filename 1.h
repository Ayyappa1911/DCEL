#include<bits/stdc++.h>
using namespace std;

class edge;
class face;



class vertex{
    private:
        double x,y;
        int vertex_index;
        vertex *next_vertex;
        vertex *prev_vertex;
    
    public:
        void vertex_cons(double X,double Y,vertex *nextvertex,vertex *prevvertex)
        {
            x = X;
            y = Y;
            next_vertex = nextvertex;
            prev_vertex = prevvertex;
        }

        double getx()
        {
            return x;
        }
        double gety()
        {
            return y;
        }
        int getvertexindex()
        {
            return vertex_index;
        }
        vertex* getnextvertex()
        {
            return next_vertex;
        }
        vertex* getprevvertex()
        {
            return prev_vertex;
        }



        void setx(double X)
        {
            x = X;
        }
        void sety(double Y)
        {
            y = Y;
        }
        void setvertexindex(int vertexindex)
        {
            vertex_index = vertexindex;
        }
        void setnextvertex(vertex* nextvertex)
        {
            next_vertex = nextvertex;
        }
        void setprevvertex(vertex* prevvertex)
        {
            prev_vertex = prevvertex;
        }
};

class Halfedges
{
    private:
        vertex *start_vertex;
        vertex *end_vertex;
        Halfedges *nexthalfedge;
        Halfedges *prevhalfedge;
        int edge_index_val;
        //vector<edge> v1;
        edge *edgein;
        face *facein;
    
    public:
        vertex* getstartvertex()
        {
            return start_vertex;
        } 
        vertex* getendvertex()
        {
            return end_vertex;
        }
        Halfedges *getnexthalfedge()
        {
            return nexthalfedge;
        }
        Halfedges *getprevhalfedge()
        {
            return prevhalfedge;
        }
        int getedgeindexval()
        {
            return edge_index_val;
        }
        edge* getedgein()
        {
            return edgein;
        }
        face *getfacein()
        {
            return facein;
        }


        void setstartvertex(vertex* startvertex)
        {
            start_vertex = startvertex;
        }
        void setendvertex(vertex* endvertex)
        {
            end_vertex = endvertex;
        }
        void setnexthalfedge(Halfedges* next_half_edge)
        {
            nexthalfedge = next_half_edge;
        }
        void setprevhalfedge(Halfedges* prev_half_edge)
        {
            prevhalfedge = prev_half_edge;
        }
        void setedgeindexval(int edgeindexval)
        {
            edge_index_val = edgeindexval;
        }
        void setedgein(edge* edge_in)
        {
            edgein = edge_in;
        }
        void setfacein(face* face_in)
        {
            facein = face_in;
        }


};


class edge{
    private:
        vertex *vertices_in;
        int edge_index;
        Halfedges *innerhalfedge; 
        Halfedges *outerhalfedge;
        edge *next_edge;
        edge *prev_edge;
        //edge *twin;


    public:
        void edge_cons(vertex* verticesin,int edgeindex,Halfedges *inner,Halfedges *outer,edge *nextedge,edge *prevedge,edge *twin_1)
        {
            vertices_in = verticesin;
            innerhalfedge = inner;
            outerhalfedge = outer;
            edge_index = edgeindex;
            next_edge = nextedge;
            prev_edge = prevedge;
        }

        vertex* getverticesin()
        {
            return vertices_in;
        }
        int getedgeindex()
        {
            return edge_index;
        }
        Halfedges* getouterhalfedge()
        {
            return outerhalfedge;
        }
        Halfedges* getinnerhalfedge()
        {
            return innerhalfedge;
        }
        edge* getnextedge()
        {
            return next_edge;
        }
        edge* getprevedge()
        {
            return prev_edge;
        }
       
        void setverticesin(vertex* verticesin)
        {
            vertices_in = verticesin;
        }
        void setedgeindex(int edgeindex)
        {
            edge_index = edgeindex;
        }
        void setinnerhalfedge(Halfedges* inner)
        {
            innerhalfedge = inner;
        }
        void setouterhalfedge(Halfedges* outer)
        {
            outerhalfedge = outer;
        }
        void setnextedge(edge *nextedge)
        {
            next_edge = nextedge;
        }
        void setprevedge(edge *prevedge)
        {
            prev_edge = prevedge;
        }
        
};
class face
{
    private:
        int face_index;
        edge* edgesin;
        face* next_face;
        face* prev_face;
        Halfedges* halfedgesin;

    public:

        int getfaceindex()
        {
            return face_index;
        }
        edge *getedgesin()
        {
            return edgesin;
        }
        Halfedges* gethalfedgesin()
        {
            return halfedgesin;
        }
        face *getnextface()
        {
            return next_face;
        }
        face *getprevface()
        {
            return prev_face;
        }


        void setfaceindex(int faceindex)
        {
            face_index = faceindex;
        }
        void setedgesin(edge *edges_in)
        {
            edgesin = edges_in;
        }
        void sethalfedgesin(Halfedges* halfedges_in)
        {
            halfedgesin = halfedges_in;
        }
        void setnextface(face* nextface)
        {
            next_face = nextface;
        }
        void setprevface(face* prevface)
        {
            prev_face = prevface;
        }
};
void vertex_data_set(double *A,double *B,vertex *v);
void input_set(vertex *v,edge *e,Halfedges *ho,Halfedges *hi,vector<edge*> &edgev);
void makeouter(vertex *v,Halfedges *ho);
void makeinner(vertex *v,Halfedges *hi);
void output_k(vertex *v,Halfedges *ho,Halfedges *hi,edge *e,face *f,int noe,vector<edge*> &edgev,FILE *fp1);
void split(vertex *v,Halfedges *ho,Halfedges *hi,edge *e,face *f,double a,double b,vector<edge*> &edgev,int noe,int nov);
void setfaces(Halfedges *ho,Halfedges *hi,face *f);
int find_face_in(face *f,double x,double y);
void centroid(face *f,double *a,double *b);
int is_it_in_face(face *temp,double a,double b,double x,double y);
int is_sign_not_same(double a,double b,double x,double y,Halfedges *h);
void input(double *arr1,double *arr2,char const *s[]);
void extract_data(double *arr1,double *arr2,FILE *fp);
int input_1(int *arr1,int *arr2,char const *s[]);
int extract_data_1(int *arr1,int *arr2,FILE *fp);
int input_2(double *arr1,double *arr2,char const *s[]);
int extract_data_2(double *arr1,double *arr2,FILE *fp);
