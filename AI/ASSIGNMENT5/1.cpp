#include <bits/stdc++.h>
using namespace std;

struct State{
    int g,b,boat;   
};
int exploredCount;

bool isValid(int g,int b){
    int gR = 3 - g;
    int bR = 3 - b;
    if (g < 0 || g > 3 || b < 0 || b > 3) return false;
    if (g > 0 && b > g)return false;
    if (gR > 0 && bR > gR) return false;
    return true;
}

bool isGoal(State s){
    return (s.g == 0 && s.b == 0 && s.boat == 1);
}

bool DLS(State curr,int depth,int limit,bool visited[4][4][2]) {
    exploredCount++;
    if (isGoal(curr)) return true;
    if (depth == limit) return false;
    visited[curr.g][curr.b][curr.boat] = true;

    int moves[5][2] = {{1,0},{2,0},{0,1},{0,2},{1,1}};

    for (int i=0;i<5;i++){
        State next = curr;
        if(curr.boat == 0){
            next.g -= moves[i][0];
            next.b -= moves[i][1];
            next.boat = 1;
        }else{
            next.g += moves[i][0];
            next.b += moves[i][1];
            next.boat = 0;
        }
        if(isValid(next.g, next.b) && !visited[next.g][next.b][next.boat]){
            if(DLS(next, depth + 1, limit, visited)) return true;
        }
    }
    return false;
}

void IDS(State start){
    int totalExplored = 0;
    for (int limit = 0; limit <= 15; limit++) {
        bool visited[4][4][2] = {false};
        exploredCount = 0;
        if (DLS(start,0,limit,visited)){
            totalExplored += exploredCount;
            cout << "IDS Found Solution at depth "<< limit << endl;
            cout << "Total States Explored: "<< totalExplored << endl;
            return;
        }

        totalExplored += exploredCount;
    }
    cout << "No Solution Found\n";
}

int main() {
    State start = {3,3,0};
    cout << "=====Depth Limited Search (limit=3)=====\n";
    bool visited[4][4][2] = {false};
    exploredCount = 0;

    if(DLS(start,0,3,visited)) {
        cout << "Solution Found within depth 3\n";
    }else{
        cout << "No Solution within depth 3\n";
    }
    cout << "States Explored: "<< exploredCount << endl;
    cout << "\n===== Iterative Deepening Search =====\n";
    IDS(start);
    return 0;
}