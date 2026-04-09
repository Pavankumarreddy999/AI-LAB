#include<bits/stdc++.h>
using namespace std;

struct state{
    vector<int> path;
    int cost;

    bool operator<(const state &other) const{
        return cost < other.cost; 
    }
};

vector<vector<int>> graph = {
    {0, 10, 15, 20, 25, 30, 35, 40},
    {12, 0, 35, 15, 20, 25, 30, 45},
    {25, 30, 0, 10, 40, 20, 15, 35},
    {18, 25, 12, 0, 15, 30, 20, 10},
    {22, 18, 28, 20, 0, 15, 25, 30},
    {35, 22, 18, 28, 12, 0, 40, 20},
    {30, 35, 22, 18, 28, 32, 0, 15},
    {40, 28, 35, 22, 18, 25, 12, 0}
};

bool visited(vector<int>&path,int city){
    for(int i=0;i<path.size();i++){
        if(path[i] == city) return true;
    }
    return false;
}

state localbeamsearch(int k){
    vector<state> beam;

    for(int i=1;i<8;i++){
        vector<int> path = {0,i};
        beam.push_back({path,graph[0][i]});
    }

    sort(beam.begin(),beam.end());
    beam.resize(min(k,(int)beam.size()));

    state best;
    best.cost = INT_MAX;

    while(true){
        vector<state> newstates;

        for(auto state : beam){

            if(state.path.size() == 8){
                int finalcost = state.cost + graph[state.path.back()][0];

                if(finalcost < best.cost){
                    vector<int> temp = state.path;
                    temp.push_back(0);
                    best = {temp,finalcost};
                }
                continue;
            }

            for(int i=0;i<8;i++){
                if(!visited(state.path,i)){
                    vector<int> newpath = state.path;
                    newpath.push_back(i);
                    int newcost = state.cost + graph[state.path.back()][i];
                    newstates.push_back({newpath,newcost});
                }
            }
        }

        if(newstates.empty()) break;

        sort(newstates.begin(),newstates.end());
        beam.clear();

        for(int i=0;i<min(k,(int)newstates.size());i++){
            beam.push_back(newstates[i]);
        }
    }

    return best;
}

int main(){
    vector<int> ks = {3, 5, 10,35};
    for (int k : ks) {
        cout << "\nBeam Width k = " << k << endl;
        state result = localbeamsearch(k);
        cout << "Path: ";
        for (int city : result.path) {
            cout << char('A' + city) << " ";
        }
        cout << "\nCost: " << result.cost << endl;
    }
    return 0;
}