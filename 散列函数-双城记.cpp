#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct ha{
	long long word[100];
};

vector<long long>words;

long long po(int up,int down){
	long long out=1;
	while(up){
		out*=down;
		up--; 
	} 
	return out;
}

void insert(string tmp){
	long long out=0;
	int n=tmp.size()-1;
	for(int i=0;i<tmp.size();i++){
		out += (tmp[i]-'a'+1)*po(n,26);
	}
	words.push_back(out);
}

void init(){
	ifstream artical;
	artical.open("A Tale of Two Cities - Charles Dickens.txt");
	string line;
	while(getline(artical,line)){
		string tmp="";
		for(int i=0;i<line.size();i++){
			if(line[i]>='a' && line[i]<= 'z')tmp.push_back(line[i]);
			else if(line[i]>='A' && line[i]<= 'Z')tmp.push_back(line[i]+'a'-'A');
			else{
				insert(tmp);
				tmp="";
			}
		}
		if(tmp != ""){
			insert(tmp);
			tmp="";
		}
	}
}

void ha_sh(){
	for(int i=0;i<words.size();i++){
		cout<<words[i]%97<<"\t";
	}
}

int main(){
	ha _hash[100]={0};
	init();
//	ha_sh();
cout<<words.size();
	return 0;
}

