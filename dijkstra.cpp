#include<iostream>
using namespace std;

const int V=4;
const int INF=1000000000;

void dijkstra(int source, int GRAPH[V][V], int parent[V], int distance[V]){
    bool visited[V] = {false};

    for(int i=0 ; i<V ; i++){
        parent[i]=-1;
        distance[i]=INF;
    }
    distance[source]=0;

    for(int count=0 ; count<V-1 ; count++){
    int u=-1;
    for(int i=0 ; i<V ; i++){
        if(!visited[i] && (u==-1 || distance[i] < distance[u])){
            u=i;
        }
    }
    visited[u]=true;

    for(int v=0 ; v<V ; v++){
        if(!visited[v] && GRAPH[u][v]!=-1 && distance[u]+GRAPH[u][v]<distance[v]){
            distance[v] = distance[u] + GRAPH[u][v];
            parent[v]=u;
        }
    }

    }
}

void print(int target , int parent[V]){
    if(target == -1){return;}
    print(parent[target],parent);
    cout<<target<<" ";
}

int main(){
    int GRAPH[V][V]={
        { 0, 10, 3, -1 },
        { -1, 0, 1, 2 },
        { -1, 4, 0, 8 },
        { -1, -1, 9, 0 }
    };

    int parent[V];
    int distance[V];
    int target=3;
    int source=0;

    dijkstra(source, GRAPH,parent,distance);

    cout<<"Shorest path is:";
    print(target,parent);
    cout<<endl<<"Total cost is:"<<distance[target];
}
