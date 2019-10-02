#include <iostream>
using namespace std;

enum RBTColor{RED, BLACK};

class RBTNode{
public:
    RBTColor color;
    int low, high;
    RBTNode *left;
    RBTNode *right;
    RBTNode *parent;
    RBTNode(int Lvalue, int Hvalue, RBTColor c,RBTNode *p,RBTNode *l, RBTNode *r):
            low(Lvalue),high(Hvalue),color(c),parent(p),left(l),right(r){}
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

    // �������뵽�������
    void insert(int low, int high){
        RBTNode *z = nullptr;
        if((z = new RBTNode(low, high, BLACK, nullptr, nullptr, nullptr)) == nullptr)
            return;
        insert(mroot, z);
    };

    // ��ѯ�Ƿ���������
    RBTNode* search_range(int key){
        RBTNode *node=mroot;
        while(node != nullptr){
            if (node->low > key)
                node = node->left;
            else if (node->high < key)
                node = node->right;
            else return node;
        }
        return node;
    }

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
            cout<< tree->low <<" ";
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
    // ���뺯��
    void insert(RBTNode* &root, RBTNode* node){
        RBTNode *x = root;
        RBTNode *y = nullptr;
        while (x != nullptr){
            y = x;
            if(node->low < x->low)
                x = x->left;
            else
                x = x->right;
        }
        node->parent = y;
        if(y != nullptr){
            node->color = RED;
            if(node->low < y->low)
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
    tree.insert(1643, 2033);
    tree.insert(5532, 7643);
    tree.insert(8999, 10332);
    tree.insert(5666653, 5669321);
    RBTNode* answer = tree.search_range(9122);
    if (answer != nullptr) {
        cout<<"Yes"<<endl;
        cout<<"Range is: ["<<answer->low<<", "<<answer->high<<"]\n";
    }
    else cout<<"No"<<endl;
    return 0;
}
