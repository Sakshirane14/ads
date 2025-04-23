#include<iostream>
using namespace std;

const int V =5;
const int INF =100000;



void prims(int GRAPH[V][V] ,int V , string department[]){
    bool selected[V]={false};
    selected[0] = true;
    int totalweight=0;

    for(int count=0 ; count<V-1 ; count++){ //loop through
        int min=INF , x=-1 , y=-1;
        for(int i=0 ; i<V ;i++){  //find smallest to adjacent
            if(selected[i]){
                for(int j=0 ; j<V ; j++){
                    if(!selected[j] && GRAPH[i][j] && GRAPH[i][j]<min){
                        min = GRAPH[i][j];
                        x=i;
                        y=j;
                    }
                }
            }
        }
        if(x!=-1 && y!=-1){
            cout<<department[x]<<"-"<<department[y]<<"\t \t"<<" distance"<<min<<endl;
            selected[y]=1;
            totalweight+=min;
        }
    }
    cout<<"Total MST Distance:"<<totalweight<<endl;
}

int main(){
    string department[V]={
        "CS","IT","ENTC","Mech","Civil"
    };
    int GRAPH[V][V]={
        {0, 2, 0, 6, 0},   // A
        {2, 0, 3, 8, 5},   // B
        {0, 3, 0, 0, 7},   // C
        {6, 8, 0, 0, 9},   // D
        {0, 5, 7, 9, 0}    // E
    };
    prims(GRAPH ,V ,department);
}
