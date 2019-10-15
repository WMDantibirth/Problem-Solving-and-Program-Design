#include <iostream>
using namespace std;

class regionTreeNode
{
public:
	int left;  //左端点值
	int right;  //右端点值
	int cover;  //被覆盖的次数
	regionTreeNode *leftChild;  //指向左孩子的指针
	regionTreeNode *rightChild;  //指向右孩子的指针
	regionTreeNode(): left(0), right(0), cover(0), leftChild(NULL), rightChild(NULL){}  //构造函数
};

//建立二叉树
regionTreeNode* createRegionTree(int min, int max)
{
	regionTreeNode *rootNode = new regionTreeNode();
	rootNode->left = min;
	rootNode->right = max;
	if (max == min)
		return rootNode;
	if (max - min == 1)
	{
		rootNode->leftChild = createRegionTree(min, min); 
		rootNode->rightChild = createRegionTree(max, max);
	}
	else 
	{
		int mid = (min + max) >> 1;
		rootNode->leftChild = createRegionTree(min, mid);  //递归构造左子树
		rootNode->rightChild = createRegionTree(mid+1, max);  //递归构造右子树
	}
	return rootNode;
}

//插入一条线段
void insertRegion(int a, int b, regionTreeNode *tree)
{
	if (tree == NULL || a < tree->left || b > tree->right)
		return;
	if (tree->left == a && tree->right == b)
	{
		tree->cover++;
		return;
	}
	int mid = (tree->left + tree->right) >> 1;
	if (b <= mid)
		insertRegion(a, b, tree->leftChild);
	else if (a >= mid)
		insertRegion(a, b, tree->rightChild);
	else
	{
		insertRegion(a, mid, tree->leftChild);
		insertRegion(mid, b, tree->rightChild);
	}
}

void show(regionTreeNode *tree){
	if(tree == NULL) return;
	cout<<"["<<tree->left<<", "<<tree->right<<", "<<tree->cover<<"]\n";
	show(tree->leftChild);
	show(tree->rightChild);
}

int main()
{
	regionTreeNode * root = createRegionTree(0, 10);
	insertRegion(6,6,root);
	show(root);
}

