#include <iostream>
#define N 10000
using namespace std;

enum RBTColor{RED, BLACK};

class RBTNode{
	public:
		RBTColor color;
		int key;
		RBTNode *left;
		RBTNode *right;
		RBTNode *parent;
		RBTNode(int value,RBTColor c,RBTNode *p,RBTNode *l, RBTNode *r):
		    key(value),color(c),parent(p),left(l),right(r){}
};

class RBTree{
	public:
		RBTNode *mroot;
		RBTree(){
		    mroot = nullptr;
		};
		~RBTree(){
		    destroy(mroot);
		};

		// ǰ�����"�����"
        void preOrder(){
            preOrder(mroot);
        };
        // ͳ�ƺ�����ĺ�����
        int numberOfRed(){
            return numberOfRed(mroot);
        }
        // ͳ�ƺ�����ĸ߶�
        int height(){
            return height(mroot);
        }
//        // �������"�����"
//        void inOrder();
//        // �������"�����"
//        void postOrder();
//
//        // (�ݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ�
//        RBTNode* search(int key);
//        // (�ǵݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ�
//        RBTNode* iterativeSearch(int key);
//
//        // ������С��㣺������С���ļ�ֵ��
//        int minimum();
//        // ��������㣺���������ļ�ֵ��
//        int maximum();
//
//        // �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
//        RBTNode* successor(RBTNode *x);
//        // �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
//        RBTNode* predecessor(RBTNode *x);

        // �����(keyΪ�ڵ��ֵ)���뵽�������
        void insert(int key){
            RBTNode *z = nullptr;
            if((z = new RBTNode(key, BLACK, nullptr, nullptr, nullptr)) == nullptr)
                return;
            insert(mroot, z);
        };

//        // ɾ�����(keyΪ�ڵ��ֵ)
//        void remove(int key);
//
        // ���ٺ����
        void destroy(){
			destroy(mroot); 
		};

    private:
        // ǰ�����"�����"
        void preOrder(RBTNode* tree) const{
            if (tree != nullptr){
                cout<< tree->key <<" ";
                preOrder(tree->left);
                preOrder(tree->right);
            }
        };
        // ͳ�ƺ�����ĺ�����
        int numberOfRed(RBTNode* node){
            int out = 0;
            if(node != nullptr){
                if(node->color==RED)
                    out++;
                out=out+numberOfRed(node->left)+numberOfRed(node->right);
            }
            return out;
        };
        // ͳ�ƺ�����߶�
        int height(RBTNode* node){
            if (node == nullptr) return 0;
            int l=height(node->left),r=height(node->right);
            if(l > r)
                return l+1;
            else
                return r+1;
        };
//        // �������"�����"
//        void inOrder(RBTNode* tree) const;
//        // �������"�����"
//        void postOrder(RBTNode* tree) const;
//
//        // (�ݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
//        RBTNode* search(RBTNode* x, int key) const;
//        // (�ǵݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
//        RBTNode* iterativeSearch(RBTNode* x, int key) const;
//
//        // ������С��㣺����treeΪ�����ĺ��������С��㡣
//        RBTNode* minimum(RBTNode* tree);
//        // ��������㣺����treeΪ�����ĺ����������㡣
//        RBTNode* maximum(RBTNode* tree);

        // ����
        void leftRotate(RBTNode* &root, RBTNode* x){
            RBTNode *y = x->right;
            x->right = y->left;
            if(y->left != nullptr)
                y->left->parent = x;
            y->parent = x->parent;
            if(x->parent== nullptr)
                root = y;
            else{
                if(x->parent->left == x)
                    x->parent->left = y;
                else
                    x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
        };
        // ����
        void rightRotate(RBTNode* &root, RBTNode* y){
            RBTNode *x = y->left;
            x->right = y->left;
            if(x->right != nullptr)
                x->right->parent = y;
            if(y->parent == nullptr)
                root = x;
            else{
                if(y->parent->left == y)
                    y->parent->left = x;
                else
                    y->parent->right = x;
            }
            x->parent = y->parent;
            y->parent=x;
            x->right=y;
        };
        // ���뺯��
        void insert(RBTNode* &root, RBTNode* node){
            RBTNode *x = root;
            RBTNode *y = nullptr;
            while (x != nullptr){
                y = x;
                if(node->key < x->key)
                    x = x->left;
                else
                    x = x->right;
            }
            node->parent = y;
            if(y != nullptr){
                node->color = RED;
                if(node->key < y->key)
                    y->left = node;
                else
                    y->right = node;
            }
            else {
                root = node;
                node->color = BLACK;
            }
            insertFixUp(root, node);
        };
        // ������������
        void insertFixUp(RBTNode* &root, RBTNode* node){
            RBTNode *parent, *uncle, *grandparent;
            while((parent = node->parent)&&(parent->color==RED)){
                grandparent = parent->parent;
                if(parent == grandparent->left) {
                    uncle = grandparent->right;
                    if (uncle && uncle->color == RED) {
                        uncle->color = BLACK;
                        parent->color = BLACK;
                        grandparent->color = RED;
                        node = grandparent;
                    }
                    else if (parent->right == node) {
                        leftRotate(root, parent);
                        node = parent;
                    }
                    else{
                        parent->color = BLACK;
                        grandparent->color = RED;
                        rightRotate(root, grandparent);
                    }
                }
                else{
                    uncle = grandparent->left;
                    if (uncle && uncle->color == RED) {
                        uncle->color = BLACK;
                        parent->color = BLACK;
                        grandparent->color = RED;
                        node = grandparent;
                    }
                    else if (parent->left == node) {
                        rightRotate(root, parent);
                        node = parent;
                    }
                    else{
                        parent->color = BLACK;
                        grandparent->color = RED;
                        leftRotate(root, grandparent);
                    }
                }
            }
            root->color = BLACK;
        };
//        // ɾ������
//        void remove(RBTNode* &root, RBTNode *node);
//        // ɾ����������
//        void removeFixUp(RBTNode* &root, RBTNode *node, RBTNode *parent);

        // ���ٺ����
        void destroy(RBTNode* &tree){
            if(tree == nullptr)
                return;
            if(tree->left != nullptr)
                return destroy(tree->left);
            if(tree->right != nullptr)
                return destroy(tree->right);
            delete tree;
            tree = nullptr;
        };
};

int main(){
    RBTree tree;
    for (int i = 0; i < N; ++i) {
        tree.insert(i);
    }
    double rate_of_red_nodes=(double)tree.numberOfRed()/(double)N;
    cout<<rate_of_red_nodes<<endl;
    cout<<tree.height()<<endl;
}

