#include<iostream>
#include<queue>
using namespace std;

const int n =5 , m=5 ;

int maze[n][m]={
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}
};

bool visited[n][m];
int parentX[n][m];
int parentY[n][m];

int dx[4] = {-1,1,0,0};  //directions for x axis (up,down,left,right)
int dy[4] = {0,0,-1,1};  //direction for y axis

bool isValid(int x , int y){
    return x>=0 && x<n && y>=0 && y<m && maze[x][y]==0 && !visited[x][y];
}

bool dfs(int x, int y){
    visited[x][y] = true;
    if(x==n-1 && y==m-1){  //came to destination
        return true;
    }

    for(int i=0 ; i<4 ; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];

        if(isValid(nx , ny)){
            parentX[nx][ny] = x;
            parentY[nx][ny] = y;

            if(dfs(nx,ny))
                return true;
        }
    }
    return false;
}

bool bfs(){
    queue <int> qx,qy;
    qx.push(0);
    qy.push(0);
    visited[0][0] = true;
    parentX[0][0]=-1;
    parentY[0][0]=-1;

    while(!qx.empty()){
        int x = qx.front();
        qx.pop();
        int y = qy.front();
        qy.pop();
        if(x == n-1 && y == m-1){      //already reached
            return true;
        }
        for(int i=0 ; i<4 ; i++){     //check directions
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(isValid(nx , ny)){
                visited[nx][ny] = true;
                parentX[nx][ny] = x;
                parentY[nx][ny] = y;

                qx.push(nx);
                qy.push(ny);
            }
        }
    }
    return false;
}


void printPath(int endX , int endY){
    int pathX[n*m] , pathY[n*m];
    int len = 0;

    while(endX!=-1 && endY!=-1){
        pathX[len] = endX;         //store current position
        pathY[len] = endY;

        endX = parentX[endX][endY];    //get the parent
        endY = parentY[endX][endY];

        len++;
    }
    cout<<"Path:"<<endl;
    for(int i=len-1 ; i>=0 ; i--){
        cout<<"("<<pathX[i]<<","<<pathY[i]<<") -> ";
    }
    cout<<endl;
}

int main(){
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<m ; j++){
            visited[i][j] = false;
        }
    }
    parentX[0][0]=-1;
    parentY[0][0]=-1;

    cout<<"DFS from (0,0): "<<(dfs(0,0) ? "Yes" : "No")<<endl;
    if(visited[n-1][m-1]){
        printPath(n-1,m-1);
    }

    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<m ; j++){
            visited[i][j]=false;
        }
    }
    cout<<endl<<"BFS from (0,0): "<<(bfs()?"Yes" : "No")<<endl;
    if(visited[n-1][m-1]){
        printPath(n-1,m-1);
    }
}
