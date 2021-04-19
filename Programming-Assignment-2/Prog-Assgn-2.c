#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

// defining point structure
typedef struct a
{
	double x;
	double y;
} point;

// sorting
void merge(point arr[], int l, int m, int r)  
{  
    int i, j, k;  
    int n1 = m - l + 1;  
    int n2 = r - m;  
  
    point L[n1], R[n2];  
  
    for (i = 0; i < n1; i++)  
        L[i] = arr[l + i];  
    for (j = 0; j < n2; j++)  
        R[j] = arr[m + 1 + j];  
 
    i = 0;  
    j = 0;  
    k = l; 
    while (i < n1 && j < n2) {  
        if (L[i].x <= R[j].x) {  
            arr[k] = L[i];  
            i++;  
        }  
        else {  
            arr[k] = R[j];  
            j++;  
        }  
        k++;  
    }  

    while (i < n1) {  
        arr[k] = L[i];  
        i++;  
        k++;  
    }  
  
    while (j < n2) {  
        arr[k] = R[j];  
        j++;  
        k++;  
    }  
}  
  
void mergeSort(point arr[], int l, int r)  
{  
    if (l < r) {  
        int m = l + (r - l) / 2;  
  
        mergeSort(arr, l, m);  
        mergeSort(arr, m + 1, r);  
  
        merge(arr, l, m, r);  
    }  
}

// defining stack 

struct Stack { 
    int top; 
    unsigned capacity; 
    point* array; 
}; 
  
//creating stack  
struct Stack* createStack(unsigned capacity) 
{ 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (point*)malloc(stack->capacity * sizeof(point)); 
    return stack; 
} 

  
// push method
void push(struct Stack* stack, point item) 
{ 
    
    stack->array[++stack->top] = item; 
    
} 
// pop method
void pop(struct Stack* stack) 
{  
   point item=stack->array[stack->top]; 
   stack->top--;
} 

// function to determine whether a point is on the left of the line passing through two other given points 
double isLeft(point a,point b, point c)
{
	if (((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x))>0) return 1;
	else if(((b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x))==0) return 0;
	else return -1;
	
}

// Function to compute convex hull 
int CH(point arr[],int n,int flag,point H[])
{
  struct Stack* stack = createStack(1000);
  if(flag)
  {
    push(stack,arr[0]);
    push(stack,arr[1]);
    int i=2;
    while(i<n)
    {
  	   if((isLeft(stack->array[stack->top-1],stack->array[stack->top],arr[i])>0)&&(stack->top))
  	 	 {
  	 		pop(stack);
  	 		while((isLeft(stack->array[stack->top-1],stack->array[stack->top],arr[i])>0)&&(stack->top)) pop(stack);

  	      }
  	   push(stack,arr[i]);
  	   i++;
     }
    for(i=0;i<=stack->top;i++) 
    {
  	   H[i]=stack->array[i];
    }
   return stack->top;
  }
  else
  {
     push(stack,arr[0]);
     push(stack,arr[1]);
     int i=2;
     while(i<n)
    {
  	   if((isLeft(stack->array[stack->top-1],stack->array[stack->top],arr[i])<0)&&(stack->top))
  	 	 {
  	 		pop(stack);
  	 		while((isLeft(stack->array[stack->top-1],stack->array[stack->top],arr[i])<0)&&(stack->top)) pop(stack);

  	      }
  	   push(stack,arr[i]);
  	   i++;
     }
    for(i=0;i<=stack->top;i++) 
    {
  	   H[i]=stack->array[stack->top - i];
    }
   return stack->top;
  }

}

//funtion to Compute the segments and the arcs of the boundary
void contzone(point UH[],int u,point LH[],int l,double r,point T[],point A[])
{
	
	point p;
	double m;
	double temp;
	double angle=0;
   for(int i=0;i<=u-1;i++)
   {
   	   m=(UH[i+1].y - UH[i].y)/(UH[i+1].x - UH[i].x);
   	 
   	   m=-1/m;
   	   p.x=UH[i].x + r*sqrt(1/(1+m*m));
   	   p.y=UH[i].y + m*r*sqrt(1/(1+m*m));

   	   A[2*i]=UH[i];
       
       if(isLeft(UH[i],UH[i+1],p)>0) 
       {
       	T[2*i]=p;
       	
       }
       else
       {
       p.x=UH[i].x - r*sqrt(1/(1+m*m));
   	   p.y=UH[i].y - m*r*sqrt(1/(1+m*m));
   	   T[2*i]=p;
   	   
   	   }
      
       	A[2*i+1].x=atan2(p.y-A[2*i].y,p.x-A[2*i].x);
      	
      

   	   p.x=UH[i+1].x + r*sqrt(1/(1+m*m));
   	   p.y=UH[i+1].y + m*r*sqrt(1/(1+m*m));
   	   if(isLeft(UH[i],UH[i+1],p)>0) 
       {
       	T[2*i+1]=p;
       
       }
       else
       {
       p.x=UH[i+1].x - r*sqrt(1/(1+m*m));
   	   p.y=UH[i+1].y - m*r*sqrt(1/(1+m*m));
   	   T[2*i+1]=p;
   	   
   	   }
   	  
   	   
   }
   for(int i=0;i<=l-1;i++)
   {   
   	    
       m=(LH[i+1].y - LH[i].y)/(LH[i+1].x - LH[i].x);
   	  
   	   m=-1/m;
   	   p.x=LH[i].x + r*sqrt(1/(1+m*m));
   	   p.y=LH[i].y + m*r*sqrt(1/(1+m*m));

   	   A[2*u+2*i]=LH[i];
       
       if(isLeft(LH[i],LH[i+1],p)>0) 
       {
       	T[2*u+2*i]=p;
         
       }
       else
       {
       p.x=LH[i].x - r*sqrt(1/(1+m*m));
   	   p.y=LH[i].y - m*r*sqrt(1/(1+m*m));
   	   T[2*u+2*i]=p;
   	   
   	   }
      
       	A[2*u+2*i+1].x=atan2(p.y-A[2*u+2*i].y,p.x-A[2*u+2*i].x);
       	if(	A[2*u+2*i+1].x>0) A[2*u+2*i+1].x=A[2*u+2*i+1].x-(3.141592653589793);
      	
      

   	   p.x=LH[i+1].x + r*sqrt(1/(1+m*m));
   	   p.y=LH[i+1].y + m*r*sqrt(1/(1+m*m));
   	   if(isLeft(LH[i],LH[i+1],p)>0) 
       {
       	T[2*u+2*i+1]=p;
       	
       }
       else
       {
       p.x=LH[i+1].x - r*sqrt(1/(1+m*m));
   	   p.y=LH[i+1].y - m*r*sqrt(1/(1+m*m));
   	   T[2*u+2*i+1]=p;
   	   
   	   }

   }


}

//funtion to print the segments and the arcs of the boundary
void printcontzone(int u,int l,point T[],point A[])
{   
	printf("+++ The containment zone\n");
	printf("--- Upper section\n");
	for(int i=0;i<u;i++)
	{
        //arc
        if(i==0)
        printf("    Arc     : (%0.15lf,%0.15lf) From %0.15lf to %0.15lf\n",A[2*i].x,A[2*i].y, 3.141592653589793,A[2*i+1].x);
        else
        printf("    Arc     : (%0.15lf,%0.15lf) From %0.15lf to %0.15lf\n",A[2*i].x,A[2*i].y, A[2*i-1].x,A[2*i+1].x);
        //Tangent
        printf("    Tangent : From(%0.15lf,%0.15lf) to (%0.15lf,%0.15lf)\n",T[2*i].x,T[2*i].y, T[2*i+1].x,T[2*i+1].y);

	}
	printf("    Arc     : (%0.15lf,%0.15lf) From %0.15lf to %0.15lf\n",A[2*u].x,A[2*u].y, A[2*u-1].x,0.000000000000000);

	printf("--- Lower section\n");
	for(int i=0;i<l;i++)
	{
		//arc
        if(i==0)
        printf("    Arc     : (%0.15lf,%0.15lf) From %0.15lf to %0.15lf\n",A[2*u+2*i].x,A[2*u+2*i].y, 0.000000000000000,A[2*u+2*i+1].x);
        else
        printf("    Arc     : (%0.15lf,%0.15lf) From %0.15lf to %0.15lf\n",A[2*u+2*i].x,A[2*u+2*i].y, A[2*u+2*i-1].x,A[2*u+2*i+1].x);
        //Tangent
        printf("    Tangent : From(%0.15lf,%0.15lf) to (%0.15lf,%0.15lf)\n",T[2*u+2*i].x,T[2*u+2*i].y, T[2*u+2*i+1].x,T[2*u+2*i+1].y);
	}	
	printf("    Arc     : (%0.15lf,%0.15lf) From %0.15lf to %0.15lf\n",A[0].x,A[0].y, A[2*l+2*u-1].x,-3.141592653589793);
}


int main()
{
  int n;

  scanf("%d",&n);
  double r;
  scanf("%lf",&r);

  point *arr=(point*)malloc(n*sizeof(point));
  for(int i=0;i<n;i++)
  {
  	scanf("%lf",&arr[i].x);
  	scanf("%lf",&arr[i].y);
  }
  
  mergeSort(arr, 0, n-1);  
  printf("\n\n");
  printf("\n+++ Circles after sorting\n");
  for(int i=0;i<n;i++)
  {
  	printf("    %0.15lf ",arr[i].x);
  	printf(" %0.15lf\n",arr[i].y);
  }
  
  point *H=(point*)malloc(n*sizeof(point));
  int flag=1;
  int num=CH(arr,n,flag,H);

  
  printf("\n+++ Upper hull\n");
  for(int i=0;i<=num;i++)
  { 

  	printf("    %0.15lf ",H[i].x);
  	printf(" %0.15lf\n",H[i].y);
  }
  point *UH=(point*)malloc((num+1)*sizeof(point));
  for(int i=0;i<=num;i++)
  { 
    UH[i].x=H[i].x;
    UH[i].y=H[i].y;
  }
  int u=num;

  flag=0;
  num=CH(arr,n,flag,H);
  point *LH=(point*)malloc((num+1)*sizeof(point));
  
  printf("\n+++ Lower hull\n");
  for(int i=0;i<=num;i++)
  { 
    LH[i]=H[i];
    printf("    %0.15lf ",H[i].x);
  	printf(" %0.15lf\n",H[i].y);
  }
  int l=num;
  
  point *T=(point*)malloc((2*(u+l+1))*sizeof(point));
  point *A=(point*)malloc((2*(u+l+2))*sizeof(point));

  
  contzone(UH,u,LH,l,r,T,A);
  
  printf("\n");
  
  printcontzone(u,l,T,A);
	return 0;
}
