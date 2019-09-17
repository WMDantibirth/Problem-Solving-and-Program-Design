#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
using namespace std;

vector<int>num;
int g_is_first = 1; 
int id[1000];
int sz[1000];//height
void init(){
	for(int i=0;i<1000;i++){
		id[i]=i; sz[i]=0;
	}
}
int find(int p){
	while(p!=id[p])p=id[p];
	return p;
}
void weightedQU(int p,int q)
{   int  pRoot=find(p);
    int  qRoot=find(q);     
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
   
     for(int i=0;i<1000;i++)
            if(id[i]==pid)  id[i]=qid;
}     
  
void quickunion(int p,int q)
{   int pRoot=find(p);
     int qRoot=find(q);
     
     if(pRoot==qRoot)   return ;
     
     id[pRoot]=qRoot;   
}     


int main(){
	init();
	int n,count=0;
	cin>>n;
	srand((unsigned)time(0));
	int a,b;
	a=rand()%n;
	srand((unsigned)time(0));
	b=rand()%n;
	while(not connected(a,b)){
//		myunion();
//		quickunion();
		weightedQU(a,b);
		count++;
		srand((unsigned)time(0));
		a=rand()%n;srand((unsigned)time(0));b=rand()%n;
		cout<<count<<endl;
	}
	cout<<count<<endl;
	return 0;
} 
