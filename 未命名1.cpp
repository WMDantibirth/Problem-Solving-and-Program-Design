#include <iostream>
#define n 100
using namespace std;

typedef struct node{
	int key;
	bool color;//1->black;0->red;
	struct node *left, *right;
}NODE;

//LEFT_ROTATE(T,node x)
//{
//	node y = x.right; //��ȡ�Һ���
//	x.right=y.left; //����x���Һ���Ϊy������
//	if (y.left!=NIL) y.left.parents=x;
//	y.parents=x.parents; //����y�ĸ����Ϊx�ĸ����
//	if(x.parents== NIL) T.root=y;
//	else if (x==x.parents.left) x.parents.left=y;
//	else x.parents.right= y;
//	y.left= x; //����y������Ϊx
//	x.parents=y;
//}

int main(){
	node null;
	null.color=1;
	null.key=-1;
	node root;
	root.key=0;
	root.color=1;
	root.left->null;
	root.right->null;
	
}
