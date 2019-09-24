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
//	node y = x.right; //获取右孩子
//	x.right=y.left; //设置x的右孩子为y的左孩子
//	if (y.left!=NIL) y.left.parents=x;
//	y.parents=x.parents; //设置y的父结点为x的父结点
//	if(x.parents== NIL) T.root=y;
//	else if (x==x.parents.left) x.parents.left=y;
//	else x.parents.right= y;
//	y.left= x; //设置y的左孩子为x
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
