#include<iostream>
#include<queue>
#include<vector>
using namespace std;

const int t=2; //order=4, min nodes=2

class Node{
    public:
    int keys[2*t-1];
    Node *children[2*t];
    int numkey;
    bool isleaf;

    Node(bool leaf){
        isleaf=leaf;
        numkey=0;
        for(int i=0 ; i<2*t ; i++){
            children[i]=nullptr;
        }
    }

    void insertNonFull(int key){
        int i=numkey -1;
        if(isleaf){   //insert at node
            while(i>=0 && keys[i]>key){
                keys[i+1]=keys[i];      //move the greater nodes ahead
                i--;
            }
            keys[i+1]=key;
            numkey ++;
        }
        else{   //internal insertion
            while(i>=0 && keys[i]>key)  //find the place
                i--;
            if(children[i+1]->numkey == 2*t-1){  //check if full
                splitChild(i+1, children[i+1]);  //split the middle key
                
                if(key > keys[i+1])  //adjust the key
                    i++;
            }
            children[i+1]->insertNonFull(key);
        }
    }

    void splitChild(int i,Node *child){  //split at index i
        Node *newChild =new Node(child->isleaf);  //(make new node)
        newChild->numkey = t-1; //assign it t-1 as it will split from middle (t is min and half) so t-1 (assign numkey)

        for(int j=0 ;j<t-1 ;j++){
            newChild->keys[j] = child->keys[j+t];  //copy from last of child node into new child (shift half keys to new child)
        }

        if(!child->isleaf){  //it is not a leaf node
            for(int j=0 ; j<t; j++){  //(shift the old child pointers ,right pointers to new child)
                newChild->children[j] = child->children[j+t];  //assign the children of previous child to new child
            }
        }

        child->numkey=t-1;

        for(int j=numkey ; j>=i+1 ; j--){ //starting from end (shift pointers in parent)
            children[j+1] = children[j];  //shift the children in parent node to make space for new child
        }
        children[i+1] = newChild;

        for(int j=numkey-1 ; j>=i ; j--){  //make space in parent for the middle value
            keys[j+1] = keys[j];
        }
        keys[i] = child->keys[t-1]; //add the middle value at ith position
        numkey++;
    }

    bool remove(int key){ //remove at node
        int i=0;
        while(i<numkey && keys[i]<key){  //find the position of key
            i++;
       }
       if(isleaf){
            if(i<numkey && keys[i] == key){  
                for(int j=i ; j<numkey-1 ; j++){  
                    keys[j]=keys[j+1]; //1. found- shift the keys
                }
            numkey--;
            return true;
            }
            else{ //2. not found- key not found in leaf node
                return false;
            }
       }
       if(i>=numkey){
            return children[i]->remove(key);  //3.key in child- when key is in the child
       }
       return false;
    }
};

class Btree{
    public:
    Node* root;
    Btree(){
        root=new Node(true);
    }

    void insert(int key){
        if(root->numkey == 2*t-1){ //if root is full
               Node *newRoot=new Node(false);  //create node telling it is not in leaf
               newRoot->children[0] = root;  //make the 1st children pointer point to root 
               newRoot->splitChild(0,root);  //split

               int i=0;
               if(newRoot->keys[i] < key){  //check the position to insert
                    i=1;
               }
               newRoot->children[i]->insertNonFull(key);
               root=newRoot;
        }
        else{
        root->insertNonFull(key);
        }
    }

    void levelOrder(){
        if(!root) return;

        queue<Node*> q;
        q.push(root);

        while(!q.empty()){
            int levelsize=q.size();
            while(levelsize--){
                Node * node = q.front();
                q.pop();

                for(int i=0 ; i<node->numkey ; i++){
                    cout<<node->keys[i]<<" ";
                }
                cout<<" | ";

                if(!node->isleaf){
                    for(int i=0 ; i<=node->numkey ; i++){
                        q.push(node->children[i]);
                    }
                }
            }
            cout<<endl;
        }
    }

    void remove(int key){
        bool removed = root->remove(key);
        if(!removed)
            cout<<key<<" key is not present";
        
        if(root->numkey==0 && !root->isleaf){  //root becomes empty after deleting
            Node *oldroot=root;
            root = root->children[0]; //make new root
            delete oldroot;
        }
    }
};

int main(){
    Btree tree;
    
    vector<int> values={10, 20, 5, 6, 12, 30, 7, 17};
    for(int i=0 ; i<values.size() ;i++){
        tree.insert(values[i]);
    }

    cout<<"Level order:"<<endl;
    tree.levelOrder();

    cout<<endl<<"Deleting 30:"<<endl;
    tree.remove(30);
    tree.levelOrder();
}
