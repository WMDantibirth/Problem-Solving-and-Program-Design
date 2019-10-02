#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#define N 1000000
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
        if(node != nullptr){
            if(node->color==RED)
                return 1+numberOfRed(node->left)+numberOfRed(node->right);
            else
                return numberOfRed(node->left)+numberOfRed(node->right);
        }
        else
            return 0;
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
        y->left = x->right;
        if(x->right != nullptr)
            x->right->parent = y;
        x->parent = y->parent;
        if(y->parent == nullptr)
            root = x;
        else{
            if(y->parent->right == y)
                y->parent->right = x;
            else
                y->parent->left = x;
        }
        x->right=y;
        y->parent=x;
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
            if(node->key < y->key)
                y->left = node;
            else
                y->right = node;
        }
        else
            root = node;
        node->color = RED;
        insertFixUp(root, node);
    };
    // 插入修正函数
    void insertFixUp(RBTNode* &root, RBTNode* node){
        RBTNode *parent, *grandparent;
        while((parent = node->parent)&&(parent->color==RED)){
            grandparent = parent->parent;
            if(parent == grandparent->left) {
                {
                    RBTNode *uncle = grandparent->right;
                    if (uncle && uncle->color == RED) {
                        uncle->color = BLACK;
                        parent->color = BLACK;
                        grandparent->color = RED;
                        node = grandparent;
                        continue;
                    }
                }
                if (parent->right == node) {
                    RBTNode *tmp;
                    leftRotate(root, parent);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }

                parent->color = BLACK;
                grandparent->color = RED;
                rightRotate(root, grandparent);
            }
            else{
                {
                    RBTNode *uncle = grandparent->left;
                    if (uncle && uncle->color == RED) {
                        uncle->color = BLACK;
                        parent->color = BLACK;
                        grandparent->color = RED;
                        node = grandparent;
                        continue;
                    }
                }
                if (parent->left == node) {
                    RBTNode *tmp;
                    rightRotate(root, parent);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                parent->color = BLACK;
                grandparent->color = RED;
                leftRotate(root, grandparent);
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
    int red_nodes = 0;
    int heights = 0;
    for (int p = 0; p < 100; ++p) {
        RBTree tree;
        vector<int> l;
        for (int i = 0; i < N; i++)
            l.push_back(i);
        srand((unsigned)time(0));
        random_shuffle(l.begin(),l.end());
        for (int i = 0; i < N; i++)
            tree.insert(l[i]);
        red_nodes += tree.numberOfRed();
        heights += tree.height();
    }
    double rate_of_red_nodes=(double)red_nodes/(double)N/100.0;
    cout<<"Rate of red nodes is:"<<rate_of_red_nodes<<endl;
    cout<<"Height of red black tree is:"<<heights/100.0<<endl;
}
