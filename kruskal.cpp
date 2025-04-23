#include<iostream>
using namespace std;

struct Edge{
    int src;
    int des;
    int weight;
};

const int V=6;
int parent[V];
string dep[V] = {"Cs" , "IT" ,"ENTC" , "Meach", "Civil" , "ASH" };

int find(int i){
    if(parent[i] == i){
        return i;
    }
    return parent[i] = find(parent[i]);
}

void unionset(int u,int v){
    parent[find(u)] = find(v);
}

void sortEdges(Edge edges[] ){
    for(int i=0 ; i<V-1 ; i++){
        for(int j=0 ; j<V-1 ; j++){
            if(edges[j+1].weight < edges[j].weight){
                Edge temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }
}

void kruskal(Edge edges[] , int E ,int V){
    for(int i=0 ; i<V ;i++){
        parent[i]=i;
    }
    int totalWeight=0;
    cout<<"Edges in kruskal:"<<endl;
    
    for(int i=0 ; i<E ;i++){
        int u = edges[i].src;
        int v = edges[i].des;

        if(find(u) != find(v)){   //if not in same set
            cout<<dep[u]<<"-"<<dep[v]<<"  (distance:"<<edges[i].weight<<")"<<endl;
            totalWeight += edges[i].weight;
            unionset(u,v);
        }
    }
    cout<<"TotalMST:"<<totalWeight;
}

int main(){
    Edge edges[]={
        {0, 1, 4},  {0, 2, 3},  {0, 3, 4},  {1, 2, 2},  {1, 3, 5},  
        {1, 4, 8},  {2, 3, 9},  {2, 5, 7},  {3, 4, 8},  {4, 5, 9}
    };
    int E = sizeof(edges) / sizeof(edges[0]);
    sortEdges(edges);
    kruskal(edges ,E ,V);
}
