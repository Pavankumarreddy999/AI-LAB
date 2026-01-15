#include<bits/stdc++.h>
using namespace std;
struct p{
    string s;
    vector<string> path;
    int cost;
    unordered_set<string> visited;
};
void exploration_path_cost(string src,string dest,unordered_map<string,vector<pair<string,int>>> g){
    unordered_map<string,bool> visited;
    queue<string> q;
    visited[src] = true;
    q.push(src);
    int cost = 0;
    bool found = false;
    while(!q.empty()){
        int levelsize = q.size();
        while(levelsize--){
            string s = q.front();
            q.pop();
            
            for(auto it : g[s]){
                string s1 = it.first;
                int c = it.second;
                if(s1 == dest) found = true;
                if(!visited[s1]){
                    q.push(s1);
                    visited[s1] = true;
                    cost += c;
                    if(found){
                        cout << cost;
                        return;
                    }
                }
            }
        }
        
    }
}


void bfs(string src,string dest,unordered_map<string,vector<pair<string,int>>>&g){
    queue<p> q;
    q.push({src,{src},0,{src}});
    while(!q.empty()){
        p cur = q.front();
        q.pop();

        if(cur.s == dest){
            for(auto city : cur.path){
                cout << city << " -> ";
            }
            cout << "cost :" << cur.cost << "\n";
            continue;
        }
        for(auto nbr : g[cur.s]){
            string next = nbr.first;
            int c = nbr.second;
            if(!cur.visited.count(next)){
                p a;
                a.s = next;
                a.path = cur.path;
                a.path.push_back(next);
                a.cost = cur.cost;
                a.cost += c;
                a.visited = cur.visited;
                a.visited.insert(next);
                q.push(a);
            }
        }
    }
}

void dfs(string curr,string dest,unordered_map<string,vector<pair<string,int>>> g,unordered_set<string> visited1,vector<string> pathdfs,int cost){
    if(curr == dest){
        for(auto city : pathdfs){
            cout << city << " -> ";
        }
        cout << "cost :" << cost << "\n";
        return;
    }
    for (auto &nbr : g[curr]) {
        string next = nbr.first;
        int c = nbr.second;

        if (!visited1.count(next)) {
            visited1.insert(next);
            pathdfs.push_back(next);
            dfs(next, dest, g, visited1, pathdfs, cost + c);

            pathdfs.pop_back();
            visited1.erase(next);
        }
    }
}

int main(){
    unordered_map<string,vector<pair<string,int>>> g;
    g["Chicago"] = {{"Detroit",283},{"Cleveland",345},{"Indianapolis",182}};
    g["Indianapolis"] = {{"Chicago",182},{"Columbus",176}};
    g["Cleveland"] = {{"Chicago",345},{"Detroit",169},{"Columbus",144},{"Pittsburgh",134},{"Buffalo",189}};
    g["Detroit"] = {{"Chicago",283},{"Cleveland",169},{"Buffalo",256}};
    g["Columbus"] = {{"Indianapolis",176},{"Pittsburgh",185},{"Cleveland",144}};
    g["Pittsburgh"] = {{"Cleveland",134},{"Columbus",185},{"Buffalo",215},{"Philadelphia",305},{"Baltimore",247}};
    g["Baltimore"] = {{"Pittsburgh",247},{"Philadelphia",101}};
    g["Philadelphia"] = {{"Baltimore",101},{"Pittsburgh",305},{"New york",97},{"Syracuse",253}};
    g["Buffalo"] = {{"Detroit",256},{"Cleveland",189},{"Pittsburgh",215},{"Syracuse",150}};
    g["New york"] = {{"Philadelphia",97},{"Syracuse",254},{"Boston",215},{"Providence",181}};
    g["Providence"] = {{"New york",181},{"Boston",50}};
    g["Boston"] = {{"Syracuse",312},{"Providence",50},{"New york",215},{"Portland",107}};
    g["Portland"] = {{"Boston",107}};
    g["Syracuse"] = {{"Buffalo",150},{"Philadelphia",253},{"New york",254},{"Boston",312}};

    string src = "Syracuse",dest = "Chicago";
    cout << "----------------------------exploration path cost--------------------------" << "\n";
    exploration_path_cost(src,dest,g);
    cout << "\n";
    cout << "---------BFS TO FIND ALL POSSIBLE STEP COST BETWEEN SYRACUSE TO CHICAGO--------" << "\n";
    bfs(src,dest,g);
    cout << "\n";
    cout << "---------dFS TO FIND ALL POSSIBLE STEP COST BETWEEN SYRACUSE TO CHICAGO--------" << "\n";
    unordered_set<string> visited1;
    vector<string> pathdfs;
    visited1.insert(src);
    pathdfs.push_back(src);
    dfs(src,dest,g,visited1,pathdfs,0);
    return 0;
}
