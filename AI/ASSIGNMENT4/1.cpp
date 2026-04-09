#include<bits/stdc++.h>
using namespace std;

struct Node{
    string city;
    int cost;
    vector<string> path;
    Node(string c,int co,vector<string> p){
        city=c;
        cost=co;
        path=p;
    }
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
        while(i>frontIndex&&data[i].cost<data[i-1].cost){
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

int getIndex(vector<string>&cities,string city){
    for(int i=0;i<cities.size();i++)
        if(cities[i]==city)return i;
    return -1;
}

void bestFirstSearch(vector<vector<int>>&graph,vector<string>&cities,string start,string goal){
    int n=cities.size();
    vector<bool> visited(n,false);

    priorityqueue pq;
    pq.push(Node(start,0,{start}));
    int pathsExplored=0;
    while(!pq.empty()){
        Node current=pq.top();
        pq.pop();

        int u=getIndex(cities,current.city);
        if(visited[u])continue;
        visited[u]=true;
        pathsExplored++;
        for(int i=0;i<current.path.size();i++) cout<<current.path[i]<<" -> ";
        cout<<"| Cost:"<<current.cost<<"\n";

        if(current.city==goal){
            cout<<"\nGoal Reached!\n";
            cout<<"Total Paths Explored:"<<pathsExplored<<"\n";
            return;
        }

        for(int v=0;v<n;v++){
            if(graph[u][v]!=1e9&&!visited[v]){
                vector<string> newPath=current.path;
                newPath.push_back(cities[v]);
                pq.push(Node(cities[v],current.cost+graph[u][v],newPath));
            }
        }
    }
    cout<<"Goal not reachable.\n";
}

int main(){
    vector<string> cities={"Chicago","Indianapolis","Cleveland","Detroit","Columbus","Pittsburgh","Baltimore","Philadelphia","Buffalo","New York","Providence","Boston","Portland","Syracuse"};
    const int INF=1e9;
    vector<vector<int>> adjMatrix={
        {0,182,345,283,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
        {182,0,INF,INF,176,INF,INF,INF,INF,INF,INF,INF,INF,INF},
        {345,INF,0,169,144,134,INF,INF,189,INF,INF,INF,INF,INF},
        {283,INF,169,0,INF,INF,INF,INF,256,INF,INF,INF,INF,INF},
        {INF,176,144,INF,0,185,INF,INF,INF,INF,INF,INF,INF,INF},
        {INF,INF,134,INF,185,0,247,305,215,INF,INF,INF,INF,INF},
        {INF,INF,INF,INF,INF,247,0,101,INF,INF,INF,INF,INF,INF},
        {INF,INF,INF,INF,INF,305,101,0,INF,97,INF,INF,INF,253},
        {INF,INF,189,256,INF,215,INF,INF,0,INF,INF,INF,INF,150},
        {INF,INF,INF,INF,INF,INF,INF,97,INF,0,181,215,INF,254},
        {INF,INF,INF,INF,INF,INF,INF,INF,INF,181,0,50,INF,INF},
        {INF,INF,INF,INF,INF,INF,INF,INF,INF,215,50,0,107,312},
        {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,107,0,INF},
        {INF,INF,INF,INF,INF,INF,INF,253,150,254,INF,312,INF,0}
    };

    for(int i=0;i<cities.size();i++){
        cout<<"\n----------------------------------\n";
        cout<<"Destination:"<<cities[i]<<"\n";
        bestFirstSearch(adjMatrix,cities,"Syracuse",cities[i]);
    }
    return 0;
}