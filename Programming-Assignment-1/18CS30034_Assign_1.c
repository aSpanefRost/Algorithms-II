//#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//#include<vector>
//#include<algorithm>
//#include<fstream>

//using namespace std;

int smallpath[10000];
int smallpath_len=9999;
int edge_ar[10000][10000];
int max_flow=0;
int temp=0;

typedef struct edge
{
  int y;
  int c;
  int f;
  struct edge* next;

} EDGE;

typedef struct vertex
{
  int x;
  int n;
  EDGE* p;

} VERTEX;

typedef struct graph
{
  int V;
  int E;
  VERTEX* H;

} GRAPH;

GRAPH* ReadGraph(char* fname)
{  
	//begin
    FILE *fptr; 
   
    // Open file 
    fptr = fopen(fname, "r"); ///end. // printf("%d ",k);

   //fstream file;
   int k;
   //file.open(fname);
   GRAPH* graph =(GRAPH*)malloc(sizeof(GRAPH));
 //for(int j=0;j<2;j++){{file>>i;cout<<i<<endl;}}
   
   fscanf(fptr,"%d", &k);  //No. of Vertex
   graph->V=k;

   //V=i;
   fscanf(fptr,"%d", &k);  //No. of Edge
   graph->E=k;
   //E=i;
   
   graph->H=(VERTEX*)malloc((graph->V+3)*sizeof(VERTEX));
   for(int i=1;i<=(graph->V);i++){ (graph->H[i]).x=i;fscanf(fptr,"%d", &k);/*printf("%d ",k);*/(graph->H[i]).n=k;(graph->H[i]).p=NULL;}
   for(int i=1;i<=(graph->E);i++){ EDGE* newEdge = (EDGE*)malloc(sizeof(EDGE));fscanf(fptr,"%d", &k);/*printf("%d ",k)*/; newEdge->next=(graph->H[k]).p;(graph->H[k]).p=newEdge;fscanf(fptr,"%d", &k);/*printf("%d ",k);*/newEdge->y=k;fscanf(fptr,"%d", &k);/*printf("%d ",k);*/newEdge->c=k;}
   
   return graph;
        
}

void PrintGraph(GRAPH *G)
{
   int V=G->V;
   printf("\n");
   for(int i=1;i<=V;i++){  EDGE* pointer=(G->H[i]).p;if(pointer!=NULL)printf("%d ",(G->H[i]).x);while(pointer!=NULL){printf("->{%d,%d,%d}",pointer->y,pointer->c,pointer->f);pointer=pointer->next;} printf("\n"); }//<<pointer->y<<<<pointer->c<<
}

 void Augmenting_path(GRAPH* G,int s,int t,int* visited,int* path,int path_index,int min_cap)
 {
    visited[s]=1;
    path[path_index]=s;
    path_index++;
    if(s==t)
    {
      //Call Max flow 

     for(int i=1;i<path_index;i++)
     //  printf("#%d-%d#",path[i],min_cap);
     //  printf("\n");
     //  printf("a%d %da",path_index-1,smallpath_len);
        if((path_index-1==smallpath_len)&&(min_cap>0)) 
          { 
            
            if(min_cap>temp){
            for(int i=1;i<path_index;i++) smallpath[i-1]=path[i];
            smallpath_len=path_index-1;
               temp=min_cap;
             }
           }
        else if((path_index-1<smallpath_len)&&(min_cap>0)) 
          { 
          
            for(int i=1;i<path_index;i++) smallpath[i-1]=path[i];
            smallpath_len=path_index-1;
               temp=min_cap;
             
           }
    }
    else
    {
      EDGE* pointer=(G->H[s]).p;
      while(pointer!=NULL) 
      {
        if(!visited[pointer->y]){ if(min_cap>=(pointer->c)-(pointer->f))min_cap=(pointer->c)-(pointer->f);Augmenting_path(G,pointer->y,t,visited,path,path_index,min_cap);}
        pointer=pointer->next;

      }
    }
    path_index--;
    visited[s]=0;

 }


void ComputeMaxFlow(GRAPH *G,int s,int t)
{
	int V=G->V;
	int edge_array[V+1][V+1];
	for(int i=1;i<=V;i++) for(int j=1;j<=V;j++) edge_array[i][j]=0;
    for(int i=1;i<=V;i++){EDGE* pointer=(G->H[i]).p;while(pointer!=NULL){pointer->f=0;edge_array[i][pointer->y]=1;pointer=pointer->next;}}
    for(int i=1;i<=V;i++) for(int j=1;j<=V;j++)
     if((edge_array[i][j])&&(!edge_array[j][i]))
       {
       //	printf("*%d%d*",i,j);
        edge_array[j][i]=2;
        EDGE* newEdge = (EDGE*)malloc(sizeof(EDGE));
        newEdge->next=(G->H[j]).p;
        (G->H[j]).p=newEdge;
        EDGE*pointer=(G->H[i]).p;
        while(1){
         if(pointer->y==j) {newEdge->y=i/*,printf("*%d*",pointer->y)*/;newEdge->c=pointer->c;newEdge->f=0;break;}
         else pointer=pointer->next;  }
       }

    int* visited=(int*)malloc((V+1)*sizeof(int));
    int* path=(int*)malloc((V+1)*sizeof(int));
    int path_index=1;
    for(int i=1;i<=V;i++)
    {
      visited[i]=0;
    }
    int min_cap=1000000007;
   // printf("\nh%dh\n",min_cap);
    
    smallpath[0]=0;
    while(1)
    {
     smallpath[0]=-1;
     temp=0;
     Augmenting_path(G,s,t,visited,path,path_index,min_cap);
     if(smallpath[0]==-1) break;
     max_flow+=temp;
    // printf("\n");
    // for(int i=0;i<smallpath_len;i++) printf("-%d.%d",smallpath[i],temp);
    // printf("\n");
     for(int i=1;i<smallpath_len;i++) 
     {
        EDGE* pointer=(G->H[smallpath[i-1]]).p;
        while(1)
           {
             if(pointer->y==smallpath[i]) 
                 {(pointer->f)+=temp;break;}
             else pointer=pointer->next; 
           }
        pointer=(G->H[smallpath[i]]).p;
        while(1)
          {
           if(pointer->y==smallpath[i-1]) 
                 {(pointer->f)-=temp;break;}
             else pointer=pointer->next; 
          }  


     }
    
    }

    printf("\nMax flow is %d\n",max_flow);
    for(int i=1;i<=V;i++)
      for(int j=1;j<=V;j++)
      {
        if(edge_array[i][j]==2)
        {
          EDGE* pointer=(G->H[i]).p;
          if(pointer->y==j)
          {
            *pointer=*(pointer->next);
          }
        }
      }
       
}

void NeedBasedFlow(GRAPH* G)
{
  int V=G->V;
  int sum=0;
  int check=0;
  for(int i=1;i<=V;i++) sum+=(G->H[i]).n;
//  printf("\n%d\n",sum);

  if(sum!=0){ printf("\nNeedBasedFlow Not Possible\n");return;}
  else
  {
     (G->H[V+1]).p=NULL;
     (G->H[V+2]).p=NULL;
     for(int i=1;i<=V;i++) 
      {
        if((G->H[i]).n>0)
          {
            EDGE* newEdge = (EDGE*)malloc(sizeof(EDGE));
            newEdge->next=(G->H[V+1]).p;
            (G->H[V+1]).p=newEdge;newEdge->y=i;
            newEdge->c=(G->H[i]).n;
            newEdge->f=0;
         //   EDGE* newEdge1 = (EDGE*)malloc(sizeof(EDGE));
         //   newEdge1->next=(G->H[i]).p;
        //    (G->H[i]).p=newEdge1;newEdge1->y=V+1;
         //   newEdge1->c=newEdge->c;
         //   newEdge1->f=0;
            check+=(G->H[i]).n;
          }
        if((G->H[i]).n<0)
          {
            EDGE* newEdge = (EDGE*)malloc(sizeof(EDGE));
            newEdge->next=(G->H[V+2]).p;
            (G->H[V+2]).p=newEdge;newEdge->y=i;
            newEdge->c=-(G->H[i]).n;
            newEdge->f=0;
       //     EDGE* newEdge1 = (EDGE*)malloc(sizeof(EDGE));
       //     newEdge1->next=(G->H[i]).p;
       //     (G->H[i]).p=newEdge1;newEdge1->y=V+2;
       //     newEdge1->c=newEdge->c;
       //     newEdge1->f=0;

          }
      }    

  }  
     G->V=(G->V)+2;
     smallpath_len=9999;
     smallpath[0]=-1;
     max_flow=0;
     ComputeMaxFlow(G,V+1,V+2);
     for(int i=1;i<=V;i++)
     {
      if((G->H[i]).n!=0) 
      {
        if((G->H[i]).n>0) 
        {
          EDGE* pointer=(G->H[i]).p;
          
          (G->H[i]).p=pointer->next;
     //     printf("Rahul");
          
        }
        if((G->H[i]).n<0) 
        {
          EDGE* pointer=(G->H[i]).p;
          
          (G->H[i]).p=pointer->next;
          
        }
      }
     }
     G->V=(G->V)-2;

     if(check!=max_flow) printf("\nNeedBasedFlow Not Possible\n");
}

int main()
{

   char filename[20];
   printf("Enter the filename to open \n"); 
   scanf("%s", filename); 
   //cout<<filename;
   GRAPH* G=ReadGraph(filename);
   PrintGraph(G);
   int s,t;
   printf("Enter the source and sink id respectively\n");
   scanf("%d%d",&s,&t);
   printf("\nAfter computing Max Flow:\n");
   ComputeMaxFlow(G,s,t);
   
   PrintGraph(G);
  G=ReadGraph(filename);
   
   printf("\nAfter computing NeedBasedFlow:\n");
   NeedBasedFlow(G);
   
   PrintGraph(G);
  
  return 0;

}