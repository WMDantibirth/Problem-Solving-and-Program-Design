#include<iostream>
using namespace std;
 
typedef long long ll;
const int inf = 0x3f;
int m[20];
int posgoal[20];//��������ڶ������������ÿ�����ֵ�λ�á�
int dir[4][2] = { {1,0},{0,-1},{0,1},{-1,0} };
int fac[9] = { 1,1,2,6,24,120,720,5040,40320 };
char op[4] = { 'd','l','r','u' };//��Ҳ�Ǳ���֮����������ֵ�����С���ԭ����Ϊ��dfs�������ܰ��������ҿ������������ֵ������С�ķ�ʽȥ�ѣ�����д𰸣���ôһ�������ֵ�����С�⡣
 
int hash(int s[]) {//���������ⳣ�õ����ÿ���չ��������hash��Ľ���
	int sum = 0;
	for (int i = 0; i < 9; i++)
	{
		int k = 0;
		for (int j = i + 1; j < 9; j++)
			if (s[i] > s[j])   k++;
		sum += k * fac[8 - i];
	}
	return sum+1;
}
 
int geth(int s[]) {//�����������پ�����Ԥ�����루ÿ�����ָֻ����ڶ���������������پ���ĺͣ�
	int dis = 0;
	for (int i = 0; i < 9; i++){
		if (s[i] != 9){
			int x = i / 3, y = i % 3;
			int xx = posgoal[s[i]]/3, yy = posgoal[s[i] ]%3;
			dis += abs(x - xx) + abs(y - yy);
		}
	}
	return dis;
}
 
char path[100];
int cas, nextd;
bool idaal(int loc, int depth, int pre, int limit){
	int h = geth(m);
	if (depth + h > limit){
		nextd = min(nextd, depth + h);
		return false;
	}
	if (h == 0){
		path[depth] = '\0';
		printf("Case %d: %d\n", cas, depth);
		puts(path);
		return true;
	}
	int x = loc / 3, y = loc % 3;
	for (int i = 0; i < 4; i++){
		if (pre + i == 3)    continue;
		int xx = x + dir[i][0];
		int yy = y + dir[i][1];
		if (xx < 0 || xx >= 3 || yy < 0 || yy >= 3)    continue;
		int temloc = xx * 3 + yy;
		swap(m[loc], m[temloc]);
		path[depth] = op[i];
		if (idaal(temloc, depth + 1, i, limit))   return true;
		swap(m[loc], m[temloc]);
	}
	return false;
}
 
int main(){
	int t;
	cin>>t;
	char str[50];
	for (cas = 1; cas <= t; cas++){
		int loc;
		cin>>str;
		for (int i = 0; i < 9; i++){
			if (str[i] == 'X') m[i] = 9, loc = i;
			else m[i] = str[i] - '0';
		}
		cin>>str;
		for (int i = 0; i < 9; i++){
			if (str[i] == 'X') posgoal[9] = i;
			else posgoal[str[i] - '0'] = i;
		}
		for (int limit = geth(m);; limit = nextd){
			nextd = inf;
			if (idaal(loc, 0, inf, limit))//������ص���false��������limit��ֵ
				break;
		}
	}
	return 0;
}

