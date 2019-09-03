#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int>num;

int id[10000];//假定0-99为最上面一行，9900-9999为最后一行 
int tf[10000];//是否渗透 
void init(){
	for(int i=0;i<10000;i++){
		id[i]=i; tf[i]=0;
	}
}
int find(int p){
	while(p!=id[p])p=id[p];
	return p;
}
void weighted-QU(int p){   
	int pRoot=find(p);
	if(pRoot<100){
		int p1Root=find(pRoot+100);
		id[p1Root]=pRoot;
	}
    else if(pRoot>=9900){
    	int p1Root=find(pRoot-100);
    	id[pRoot]=p1Root;
	}
	else if(pRoot%100==0){
		int p1Root=find(pRoot+1), p2Root=find(pRoot+100),
			p3Root=find(pRoot-100),m;
		m=min(p1Root,p2Root);
		m=min(pRoot,m);m=min(p3Root,m);
		
	}
}


bool judgement(){
	for(int i=9900;i<10000;i++){
		if(id[i]<100)
			return 0;
	}
	return 1;
}

void calculate(){
	long long sum;
	for(long long i=0;i<1000000;i++){
		sum+=num[i];
	}
	double ans = sum/1000000.0;
	cout<<ans<<endl;
}

int monte_carlo() {srand((unsigned)time(0)); 
    return rand()%10000; 
}

void color(){
	int flag= monte_carlo();
	while(tf[flag]){
		flag = monte_carlo();
	}
	tf[flag]=1;
	weighted-QU(flag);
}

int test(){
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
	while(i<1000000){
		num.push_back(test());
		i++;
	}
	calculate();
	return 0;
}
