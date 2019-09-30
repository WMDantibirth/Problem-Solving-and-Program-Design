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

		// 前序遍历"红黑树"
        void preOrder(){
            preOrder(mroot);
        };
        // 统计红黑树的红结点数
        int numberOfRed(){
            return numberOfRed(mroot);
        }
        // 统计红黑树的高度
        int height(){
            return height(mroot);
        }
//        // 中序遍历"红黑树"
//        void inOrder();
//        // 后序遍历"红黑树"
//        void postOrder();
//
//        // (递归实现)查找"红黑树"中键值为key的节点
//        RBTNode* search(int key);
//        // (非递归实现)查找"红黑树"中键值为key的节点
//        RBTNode* iterativeSearch(int key);
//
//        // 查找最小结点：返回最小结点的键值。
//        int minimum();
//        // 查找最大结点：返回最大结点的键值。
//        int maximum();
//
//        // 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
//        RBTNode* successor(RBTNode *x);
//        // 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
//        RBTNode* predecessor(RBTNode *x);

        // 将结点(key为节点键值)插入到红黑树中
        void insert(int key){
            RBTNode *z = nullptr;
            if((z = new RBTNode(key, BLACK, nullptr, nullptr, nullptr)) == nullptr)
                return;
            insert(mroot, z);
        };

//        // 删除结点(key为节点键值)
//        void remove(int key);
//
        // 销毁红黑树
        void destroy(){
			destroy(mroot); 
		};

    private:
        // 前序遍历"红黑树"
        void preOrder(RBTNode* tree) const{
            if (tree != nullptr){
                cout<< tree->key <<" ";
                preOrder(tree->left);
                preOrder(tree->right);
            }
        };
        // 统计红黑树的红结点数
        int numberOfRed(RBTNode* node){
            int out = 0;
            if(node != nullptr){
                if(node->color==RED)
                    out++;
                out=out+numberOfRed(node->left)+numberOfRed(node->right);
            }
            return out;
        };
        // 统计红黑树高度
        int height(RBTNode* node){
            if (node == nullptr) return 0;
            int l=height(node->left),r=height(node->right);
            if(l > r)
                return l+1;
            else
                return r+1;
        };
//        // 中序遍历"红黑树"
//        void inOrder(RBTNode* tree) const;
//        // 后序遍历"红黑树"
//        void postOrder(RBTNode* tree) const;
//
//        // (递归实现)查找"红黑树x"中键值为key的节点
//        RBTNode* search(RBTNode* x, int key) const;
//        // (非递归实现)查找"红黑树x"中键值为key的节点
//        RBTNode* iterativeSearch(RBTNode* x, int key) const;
//
//        // 查找最小结点：返回tree为根结点的红黑树的最小结点。
//        RBTNode* minimum(RBTNode* tree);
//        // 查找最大结点：返回tree为根结点的红黑树的最大结点。
//        RBTNode* maximum(RBTNode* tree);

        // 左旋
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
        // 右旋
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
        // 插入函数
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
        // 插入修正函数
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
//        // 删除函数
//        void remove(RBTNode* &root, RBTNode *node);
//        // 删除修正函数
//        void removeFixUp(RBTNode* &root, RBTNode *node, RBTNode *parent);

        // 销毁红黑树
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

