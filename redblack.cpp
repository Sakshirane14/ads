#include<iostream>
#include<vector>
using namespace std;

const bool red=false;
const bool black =true;

class Node{
    public:
    int data;
    bool color;
    Node *left ;
    Node *right;
    Node *parent;

    Node(int val){
        data=val;
        color=red;  //always red in for new node by default
        left=right=parent=nullptr;
    }
};

class DirectoryTree{
    Node *root;

    void rotationLeft(Node *x){
        Node *y = x->right;
        x->right = y->left;     //shift t2(y->left)

        if(y->left!=nullptr){   //update the parent of t2
            y->left->parent = x;
        }

        y->parent = x->parent;  //update parent ,as y is now going on place of x

        if(x->parent==nullptr){  
            root = y;
        }
        else if(x == x->parent->left){  //if x is x child of the parent
            x->parent->left = y;
        }
        else {  //if x is the right child of the parent
            x->parent->right = y;
        }

        y->left=x;  //change y->left to x
        x->parent = y; 
    }

    void rotationRight(Node *x){
        Node *y = x->left;
        x->left = y->right;

        if(y->right != nullptr){
            y->right->parent = x;
        }

        y->parent = x->parent;

        if(x->parent == nullptr){
            root = y;
        }
        else if(x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }

        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node *node){
        while(node != root && node->parent->color == red){  //node present in leaf and parent is red so it violates the rule
            Node *parent = node->parent;
            Node *grandparent = node->parent->parent;
            
            if(parent == grandparent->left){
                Node *uncle = grandparent->right;

                if(uncle != nullptr && uncle->color == red){  //1. uncle and parent both r red hence we can change without rotation
                    uncle->color = black;
                    parent->color = black;
                    grandparent->color = red;
                    node = grandparent;  //move node to fix violations
                }
                else{
                    if(node == parent->right){  //2. uncle is black or does not exist and node->right of parent
                        node = parent;
                        rotationLeft(node);
                    }
                    parent->color = black;  //3.now they are left skewed
                    grandparent->color = red;
                    rotationRight(grandparent);
                }
            }

            else{ //mirror case study parent is right child of grandparent
                Node *uncle = grandparent -> left;
                
                if(uncle != nullptr && uncle->color == red){
                    uncle->color = black;
                    parent->color = black ;
                    grandparent->color = red;
                    node = grandparent;
                }
                else{
                    if(node == parent->left){
                        node = parent;
                        rotationRight(node);
                    }
                    parent->color = black;
                    grandparent->color = red;
                    rotationLeft(grandparent);
                }
            }
        }
        root->color = black;
    }

    void inorder(Node *node){
        if(node==nullptr) return;
        inorder(node->left);
        cout<<node->data;
        if(node->color == red){
            cout<<"[R]"<<" ";
        }
        else{
            cout<<"[B]"<<" ";
        }
        inorder(node->right);
    }

    public:
    DirectoryTree(){
        root=nullptr;
    }

    void insert(int val){
        Node *newNode = new Node(val);
        Node *parent = nullptr;
        Node *current = root;

        while(current){
            parent = current;
            if(val < current->data){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }

            newNode->parent = parent; //set the parent of new node
            if(parent == nullptr){
                root = newNode;
            }
            else if(parent->data > val) parent->left = newNode;
            else parent->right = newNode;
            fixInsert(newNode);
    }

    void display(){
        cout<<"Inorder:"<<endl;
        inorder(root);
        cout<<endl;
    }
};

int main(){
    DirectoryTree tree;
    vector<int> val = {10, 20, 30, 5, 15, 25, 1};
    for(int i=0 ; i<val.size();i++){
        tree.insert(val[i]);
    }
    tree.display();
}
