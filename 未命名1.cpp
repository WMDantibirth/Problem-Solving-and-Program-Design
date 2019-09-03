#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

vector<int>num;
int g_is_first = 1; 
int id[100];//假定0-9为最上面一行，90-99为最后一行 
int tf[100];//是否渗透 
void init(){
	cout<<"init"<<endl;
	for(int i=0;i<100;i++){
		id[i]=i; tf[i]=0;
	}
	for(int i=0;i<10;i++)id[i]=0;
}
int find(int p){
	while(p!=id[p])p=id[p];
	return p;
}
bool cmp(int p,int q){
	return (id[p]<id[q]);
}
void weightedQU(int p){ 
	cout<<"weight"<<endl;  
	int pRoot=find(p);
	if(pRoot<10){
		if(tf[pRoot]==1){
			int p1Root=find(pRoot+10);
			id[p1Root]=0;
		}
	}
    else if(pRoot>=90){
    	if(tf[pRoot-10]){
    		int p1Root=find(pRoot-10);
    		id[pRoot]=p1Root;
		}	
	}
	else if(pRoot%10==0){
		vector<int>tmp;
		if(tf[pRoot+1])tmp.push_back(pRoot+1);
		if(tf[pRoot+10])tmp.push_back(pRoot+10);
		if(tf[pRoot-10])tmp.push_back(pRoot-10);
		if(tmp.size()!=0){
			if(tmp.size()==1)
				(id[tmp[0]]<pRoot) ? (pRoot=tmp[0]) : (id[tmp[0]]=pRoot);
			else{
				sort(tmp.begin(),tmp.end(),cmp);
				for(int i=1;i<tmp.size();i++)
					id[tmp[i]]=id[tmp[0]];
			}
		}
	}
	else if(pRoot%10==9){
		vector<int>tmp;
		if(tf[pRoot-1])tmp.push_back(pRoot-1);
		if(tf[pRoot+10])tmp.push_back(pRoot+10);
		if(tf[pRoot-10])tmp.push_back(pRoot-10);
		if(tmp.size()!=0){
			if(tmp.size()==1)
				(id[tmp[0]]<pRoot) ? (pRoot=tmp[0]) : (id[tmp[0]]=pRoot);
			else{
				sort(tmp.begin(),tmp.end(),cmp);
				for(int i=1;i<tmp.size();i++)
					id[tmp[i]]=id[tmp[0]];
			}
		}
	}
	else{
		vector<int>tmp;
		if(tf[pRoot+1])tmp.push_back(pRoot+1);
		if(tf[pRoot-1])tmp.push_back(pRoot-1);
		if(tf[pRoot+10])tmp.push_back(pRoot+10);
		if(tf[pRoot-10])tmp.push_back(pRoot-10);
		if(tmp.size()!=0){
			if(tmp.size()==1)
				(id[tmp[0]]<pRoot) ? (pRoot=tmp[0]) : (id[tmp[0]]=pRoot);
			else{
				sort(tmp.begin(),tmp.end(),cmp);
				for(int i=1;i<tmp.size();i++)
					id[tmp[i]]=id[tmp[0]];
			}
		}
	}
}


bool judgement(){
	cout<<"judgement"<<endl;
	for(int i=90;i<100;i++){
		if(id[i]==0)
			return 1;
	}
	for(int i=90;i<100;i++)
		cout<<i<<":"<<id[i]<<" ";
	cout<<endl;
	return 0;
}

void calculate(){
	cout<<"calculate"<<endl;
	long long sum=0;
	for(int i=0;i<2;i++){
		sum+=num[i];
	}
	cout<<sum/2<<endl;
}

int monte_carlo() {
	cout<<"random"<<endl;
	srand((unsigned)time(0));
	int i = rand()%100;
    return i;
}

void color(){
	cout<<"color"<<endl;
	int flag= monte_carlo();
	while(tf[flag]){
		flag = monte_carlo();
	}
//	int flag=0;
//	while(tf[flag])flag++;
	cout<<"flag="<<flag<<endl;
	tf[flag]=1;
	weightedQU(flag);
}

int test(){
	cout<<"test"<<endl;
	init();
	int count=0;//次数 
	while(1){
		if(judgement()){
			return count;
		}
		color();
		count++;
	}
}

int main(){
	long long i=0;
	while(i<2){
		cout<<i<<endl;
		num.push_back(test());
		i++;
	}
	calculate();
	return 0;
}
