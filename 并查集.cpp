#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#define N 10000
using namespace std;

vector<int>num;
int g_is_first = 1; 
int id[N];
int sz[N];//height
void init(){
	for(int i=0;i<N;i++){
		id[i]=i; sz[i]=0;
	}
}
int find(int n){
	int p=n;
	while(p!=id[p])p=id[p];
	if(p!=n){
		id[n]=p;
		sz[n]=sz[p]+1;
	}
	return p;
}
int new_find(int p)
{
	while(p!=id[p])p=id[p];
	return p;
}
void weightedQU(int p,int q)
{   int  pRoot=new_find(p);
    int  qRoot=new_find(q);     
    if (pRoot==qRoot)   return ;
    if ( sz[pRoot]== sz[qRoot] )
        { id[pRoot]=qRoot; sz[qRoot]++;}
    else   if (sz[pRoot]<sz[qRoot])   
        id[pRoot]=qRoot;
    else   id[qRoot]=pRoot; 
}
bool connected(int a,int b){
	return find(a)==find(b);
} 
int quickfind(int p)
{  return id[p];}     

void myunion(int p,int q)
{   int pid=quickfind(p);
     int qid=quickfind(q);
     
     if(pid==qid)   return ;
   
     for(int i=0;i<N;i++)
            if(id[i]==pid)  id[i]=qid;
}     
  
void quickunion(int p,int q)
{   int pRoot=new_find(p);
    int qRoot=new_find(q); 
    if(pRoot==qRoot)   return ;
    id[pRoot]=qRoot;   
}     
void Weighted_QU_With_Path_Compression(int p,int q)
{   int  pRoot=find(p);
    int  qRoot=find(q);     
    if (pRoot==qRoot)   return ;
    if ( sz[pRoot]== sz[qRoot] )
        { id[pRoot]=qRoot; sz[qRoot]++;}
    else   if (sz[pRoot]<sz[qRoot])   
        id[pRoot]=qRoot;
    else   id[qRoot]=pRoot; 
}

int main(){
	int T=1000000;
	double average_time=0.0;
	for(int x=0;x<T;x++){
		init();
		int n,count=0;
		n=N;
		srand(time(0));
		int a,b;
		a=rand()%n;
		b=rand()%n;
		clock_t start,end;
		start=clock(); 
		while(not connected(a,b)){
//			myunion(a,b);
//			quickunion(a,b);
//			weightedQU(a,b);
			Weighted_QU_With_Path_Compression(a,b);
			count++;
			a=rand()%n;
			b=rand()%n;
//			cout<<count<<endl;
		}
		end=clock();
		double end_time = (double)(end-start);
		average_time+=end_time;
	}
	average_time/=T;
	cout<<"Average time:"<<average_time<<"ms"<<endl; 
//	cout<<count<<endl;
	return 0;
} 
