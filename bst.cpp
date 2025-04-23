#include<iostream>
#include<queue>
using namespace std;

struct Node{
    int key;
    Node *left;
    Node*right;
    int height;
    Node(int data){
        left=right=nullptr;
        key=data;
        height=1;
    }
};

class BST{
    private:
    Node*root;
    Node*root2;

    Node *insert(Node *root,int key){
        if(root == nullptr){
            return new Node(key);
        }
        if(key < root->key){
            root->left=insert(root->left , key);
        }
        else if(key > root->key){
            root->right = insert(root->right , key);
        }
            return root;
    }

    void postorder(Node *root){
        if(root==nullptr) return;
        postorder(root->left);
        postorder(root->right);
        cout<<root->key<<" ";
    }

    int heightNonRecursive(Node *root){
        queue<Node*> q;
        q.push(root);
        int height =-1;

        while(!q.empty()){
            int levelsize = q.size();
            height++;

            while(levelsize --){
                Node *current = q.front();
                q.pop();
                if(current->left != nullptr){q.push(current->left);}
                if(current->right != nullptr){q.push(current->right);}
            }
        }
        return height;
    }

    int height(Node *root){
        if(root==nullptr){
            return -1;
        }
        int left = height(root->left);
        int right = height(root->right);
        return 1 + max(left,right);
    }

    int Sumup(Node*root){
        if(root==nullptr){
            return 0;
        }
        int left = Sumup(root->left);
        int right = Sumup(root->right);

        root->key += left+right;
        return root->key;
    }

    bool equaltrees(Node*root1 , Node *root2){
        if(root1==nullptr && root2==nullptr)
            return true;
        if(root1==nullptr || root2==nullptr)
            return false;
        return (root1->key == root2->key) && equaltrees(root1->left,root2->left) && equaltrees(root1->right,root2->right);
    }

    public:
    BST(){
        root=nullptr;
        root2 = nullptr;
    }
    void insertNode(int key){
        root = insert(root,key);
    }

    void height(){
        cout<<"Height of bst:"<<height(root)<<endl;
        cout<<"Height of bst(non recursive):"<<heightNonRecursive(root)<<endl;
    }

    void display(){
        cout<<"Dispaly BST:"<<endl;
        postorder(root);
    }

    void sum(){
        Sumup(root);
    }

    bool checkequal(BST &other){
        return equaltrees(this->root , other.root);
    }

};

int main(){
    BST b;
    b.insertNode(10);
    b.insertNode(5);
    b.insertNode(30);
    b.insertNode(25);
    b.insertNode(20);

    BST b1;
    b1.insertNode(10);
    b1.insertNode(5);
    b1.insertNode(30);
    b1.insertNode(25);
    b1.insertNode(20);

    if(b.checkequal(b1)){
        cout<<"They are equal"<<endl;
    }
    else{
        cout<<"Not equal"<<endl;
    }


    b.display();
    cout<<endl;
    b.height();

    b.sum();
    cout<<"After summinup:";
    b.display();
}
