#include<bits/stdc++.h>
using namespace std;

struct Node{
    int x,y;
    int priority;
};

class priorityqueue{
    vector<Node> data;
    int frontIndex;
public:
    priorityqueue(){
        frontIndex=0;
    }
    void push(Node x){
        data.push_back(x);
        int i=data.size()-1;
        while(i>frontIndex&&data[i].priority<data[i-1].priority){
            swap(data[i],data[i-1]);
            i--;
        }
    }
    void pop(){
        frontIndex++;
    }
    Node top(){
        return data[frontIndex];
    }
    bool empty(){
        return frontIndex>=data.size();
    }
};

int evaluationCost(int x1,int y1,int x2,int y2){
    return abs(x1-x2)+abs(y1-y2);
}

void bestFirstSearch(vector<vector<int>>&grid,pair<int,int> entry,pair<int,int> exitPoint){
    int n=grid.size();
    int m=grid[0].size();

    vector<vector<bool>> visited(n,vector<bool>(m,false));
    priorityqueue pq;
    int initialPriority=evaluationCost(entry.first,entry.second,exitPoint.first,exitPoint.second);
    pq.push({entry.first,entry.second,initialPriority});

    vector<int> dx={-1,1,0,0};
    vector<int> dy={0,0,-1,1};
    int explored=0;

    while(!pq.empty()){
        Node current=pq.top();
        pq.pop();

        if(visited[current.x][current.y])continue;

        visited[current.x][current.y]=true;
        explored++;
        cout<<"("<<current.x<<","<<current.y<<")\n";
        if(current.x==exitPoint.first&&current.y==exitPoint.second){
            cout<<"Exit Reached\n";
            cout<<"Nodes Explored:"<<explored<<"\n";
            return;
        }
        for(int i=0;i<4;i++){
            int nx=current.x+dx[i];
            int ny=current.y+dy[i];
            if(nx>=0&&ny>=0&&nx<n&&ny<m&&grid[nx][ny]==0&&!visited[nx][ny]){
                int newPriority=evaluationCost(nx,ny,exitPoint.first,exitPoint.second);
                pq.push({nx,ny,newPriority});
            }
        }
    }
    cout<<"No path found\n";
}

int main(){
    vector<vector<int>> grid={
        {1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,0,1,0,0,0,0,1,1,0,0,1},
        {1,0,0,0,0,0,1,0,1,1,1,0,1},
        {1,1,1,1,0,1,0,0,0,0,1,1,1},
        {1,1,1,1,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,0,1,0,0,1,0,1,1,1},
        {1,0,0,1,0,1,0,1,0,1,0,0,1},
        {1,0,0,1,0,1,0,1,1,1,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1},
    };
    pair<int,int> entry={7,4};
    pair<int,int> exitPoint={4,11};
    bestFirstSearch(grid,entry,exitPoint);
    return 0;
}