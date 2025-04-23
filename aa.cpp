#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node*left;
    Node*right;
    int level;
    Node(int val){
        data=val;
        left=right=nullptr;
        level=1;
    }
};

class AAtree{
    private:
    Node *root;

    Node *skew(Node*node){
        if(node==nullptr || node->left==nullptr){
            return node;
        }
        if(node->left->level == node->level){
            Node *leftchild = node->left;
            node->left = leftchild->right;
            leftchild->right = node;
            return leftchild;
        }
        return node;
    }

    Node *split(Node *node){
        if(node==nullptr || node->right==nullptr || node->right->right==nullptr){
            return node;
        }
        if(node->right->right->level == node->level){
            Node *rightChild = node->right;
            node->right = rightChild->left;
            rightChild->left = node;
            rightChild->level++;
            return rightChild;
        }
        return node;
    }

    Node *insert(int key,Node *node){
        if(node==nullptr){
            return new Node(key);
        }
        if(key > node->data){
            node->right = insert(key,node->right);
        }
        else if(key < node->data){
            node->left = insert(key,node->left);
        }
        else{
            return node;
        }
        node = skew(node);
        node = split(node);
        return node;
    }

    bool search(Node*node ,int key){
        if(node==nullptr){return false;}
        if(key > node->data){
            return search(node->right ,key);
        }
        else if(key < node->data){
            return search(node->left ,key);
        }
        return true;
    }

    void inorder(Node *node){
        if(node==nullptr)return;
        inorder(node->left);
        cout<<node->data<<" ";
        inorder(node->right);
    }

    public:
    AAtree(){
        root =nullptr;
    }

    void insertNode(int key){
        root=insert(key , root);
    }
    void print(){
        inorder(root);
        cout<<endl;
    }
    bool searchNode(int key){
        return search(root,key);
    }
};

int main(){
    AAtree a;
    a.insertNode(10);
    a.insertNode(20);
    a.insertNode(5);
    a.insertNode(15);
    a.insertNode(25);

    a.print();

    cout<<"Find 5:";
    if(a.searchNode(5)){
        cout<<"Found";
    }
    else{cout<<"not found";}
}
