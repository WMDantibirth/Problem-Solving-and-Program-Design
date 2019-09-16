#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

vector<int>num;
int g_is_first = 1; 
int id[10000];//假定0-99为最上面一行，9900-9999为最后一行 
int tf[10000];//是否渗透 
int sz[10000];//height
void init(){
	for(int i=0;i<10000;i++){
		id[i]=i; tf[i]=0; sz[i]=0;
	}
}
int find(int p){
	while(p!=id[p])p=id[p];
	return p;
}
void weighted(int p,int q)
{   int  pRoot=find(p);
    int  qRoot=find(q);     
    if (pRoot==qRoot)   return ;
    if ( sz[pRoot]== sz[qRoot] )
        { id[pRoot]=qRoot; sz[qRoot]++;}
    else   if (sz[pRoot]<sz[qRoot])   
        id[pRoot]=qRoot;
    else   id[qRoot]=pRoot; 
}
bool cmp(int p,int q){
	return (find(p)<find(q));
}
void weightedQU(int p){ 
	int pRoot=p;
	if(pRoot<100){
		if(tf[pRoot+100]==1){
			weighted(pRoot+100,pRoot);
		}
	}
    else if(pRoot>=9900){
    	if(tf[pRoot-100]==1){
    		weighted(pRoot-100,pRoot);
		}	
	}
	else if(pRoot%100==0){
		vector<int>tmp;
		if(tf[pRoot+1])tmp.push_back(pRoot+1);
		if(tf[pRoot+100])tmp.push_back(pRoot+100);
		if(tf[pRoot-100])tmp.push_back(pRoot-100);
		if(tmp.size()!=0){
			if(tmp.size()==1)
				weighted(pRoot,tmp[0]);
			else{
				for(int i=0;i<tmp.size();i++)
					weighted(pRoot,tmp[i]);
			}
		}
	}
	else if(pRoot%100==99){
		vector<int>tmp;
		if(tf[pRoot-1])tmp.push_back(pRoot-1);
		if(tf[pRoot+100])tmp.push_back(pRoot+100);
		if(tf[pRoot-100])tmp.push_back(pRoot-100);
		if(tmp.size()!=0){
			if(tmp.size()!=0){
				if(tmp.size()==1)
					weighted(pRoot,tmp[0]);
				else{
					for(int i=0;i<tmp.size();i++)
						weighted(pRoot,tmp[i]);
				}
			}
		}
	}
	else{
		vector<int>tmp;
		if(tf[pRoot+1])tmp.push_back(pRoot+1);
		if(tf[pRoot-1])tmp.push_back(pRoot-1);
		if(tf[pRoot+100])tmp.push_back(pRoot+100);
		if(tf[pRoot-100])tmp.push_back(pRoot-100);
		if(tmp.size()!=0){
			if(tmp.size()!=0){
				if(tmp.size()==1)
					weighted(pRoot,tmp[0]);
				else{
					for(int i=0;i<tmp.size();i++)
						weighted(pRoot,tmp[i]);
				}
			}
		}
	}
}


bool judgement(){
	for(int i=9900;i<10000;i++){
		for(int j=0;j<100;j++){
			if(find(i)==find(j))return 1;
		}
	}
	return 0;
}

void calculate(){
	long long sum=0;
	for(int i=0;i<1000;i++){
		sum+=num[i];
	}
	cout<<(double)sum/10000000.0<<endl;
}

//int monte_carlo() {
//	srand((unsigned)time(0));
//	int i = rand()%100;
//    return i;
//}

void color(int flag){
//	cout<<"color"<<endl;
//	int flag= monte_carlo();
//	while(tf[flag]){
//		flag = monte_carlo();
//	}
//	int flag=0;
//	while(tf[flag])flag++;
//	cout<<"flag="<<flag<<endl;
	tf[flag]=1;
	weightedQU(flag);
}

int test(){
	init();
	vector<int>aaa;
	for(int i=0;i<10000;i++){
		aaa.push_back(i);
	} 
	srand((unsigned)time(0));
	random_shuffle(aaa.begin(),aaa.end());
	int count=0;//次数 
	while(1){
		if(judgement()){
			return count;
		}
		color(aaa[count]);
		count++;
	}
}

int main(){
	long long i=0;
	while(i<1000){
		num.push_back(test());
		i++;
	}
	calculate();
	return 0;
}

