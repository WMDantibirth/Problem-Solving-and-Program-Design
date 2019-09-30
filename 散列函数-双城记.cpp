#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <ctime>
#define hash_number 97
using namespace std;

vector<list<string>>hash_table(hash_number);
vector<unsigned long long>words;
vector<string>dict;

unsigned long long po(int up,int down){
	unsigned long long out=1;
	while(up){
		out*=down;
		up--; 
	} 
	return out;
}

void insertion(string tmp){
	unsigned long long out=0;
	int n=tmp.size()-1;
	for(int i=0;i<tmp.size();i++){
		out += (tmp[i]-'a'+1)*po(n,26);
	}
	words.push_back(out);
	bool tag=1;
	for(auto i=hash_table[out%hash_number].begin();i!=hash_table[out%hash_number].end();i++){
		if(*i==tmp){
			tag=0;break;
		}
	}
	if(tag) hash_table[out%hash_number].push_back(tmp);
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
			else if(tmp!=""){
				insertion(tmp);
				tmp="";
			}
		}
		if(tmp != ""){
			insertion(tmp);
			tmp="";
		}
	}
}

bool searching(string tmp){
	unsigned long long out=0;
	int n=tmp.size()-1;
	for(int i=0;i<tmp.size();i++){
		out += (tmp[i]-'a'+1)*po(n,26);
	}
	int ha=out%hash_number;
	bool flag=0;
	for(auto i=hash_table[ha].begin();i!=hash_table[ha].end();i++){
		if(*i==tmp)flag=1;
	}
	return flag;
}

void search_init(){
	ifstream dictionary;
	dictionary.open("dictionary.txt");
	string tmp;
	while(dictionary>>tmp)
		dict.push_back(tmp);
}

int main(){
	init();
//	cout<<words.size()<<endl;
//	for(int i=0;i<hash_number;i++){
//		cout<<hash_table[i].size()<<endl;
//	}
	search_init();
	srand(time(0));
	clock_t start,end;
	start=clock();
	for(int i=0;i<100000;i++){
	string rand_word = dict[rand()%dict.size()];
//	cout<<rand_word<<endl;
	searching(rand_word);
//	if(searching(rand_word))cout<<"Yes\n";
//	else cout<<"No\n";
	}
	end=clock();
	double average = (end-start)/100000.0;
	cout<<"The average time of each search is "<<average<<"ms."<<endl;
	return 0;
}
