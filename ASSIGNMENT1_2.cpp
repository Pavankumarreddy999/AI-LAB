#include<bits/stdc++.h>
using namespace std;

void bfs (unordered_map<string,vector<string>> &g,string src){
    int n = g.size();
    vector<string> ans;
    unordered_map<string,bool> visited;
    queue<string> q;
    ans.reserve(n);
    visited[src] = true;
    q.push(src);
    while(!q.empty()){
        int levelsize = q.size();
        while(levelsize--){
            string s = q.front();
            q.pop();
            cout << s << " ";
            for(auto it : g[s]){
                if(!visited[it]){
                    q.push(it);
                    visited[it] = true;
                }
            }
        }
        cout << "\n";
    }
}

void dfs1(unordered_map<string,vector<string>> &g,
          unordered_map<string,bool> &visited,
          string u,
          int depth) {

    visited[u] = true;
    cout << string(depth * 4, ' ') << "|__" << u << "\n";

    for(auto v : g[u]) {
        if(!visited[v]) {
            dfs1(g, visited, v, depth + 1);
        }
    }
}


void dfs(unordered_map<string,vector<string>> &g, string src) {
    unordered_map<string,bool> visited;
    dfs1(g, visited, src, 0);
}


int main(){
    unordered_map<string,vector<string>> g;
    g["Raj"]   = {"Sunil","Neha"};
    g["Akash"] = {"Sunil","Priya"};
    g["Sunil"] = {"Raj", "Maya","Sneha","Akash"};
    g["Sneha"] = {"Sunil", "Neha","Rahul"};
    g["Maya"]  = {"Sunil", "Rahul","Arjun1"};
    g["Priya"] = {"Raj","Neha", "Aarav","Akash"};
    g["Neha"]  = {"Raj", "Akash", "Aarav","Sneha"};
    g["Neha1"] = {"Priya","Neha","Rahul","Aarav"};
    g["Rahul"] = {"Neha","Neha1","Sneha","Pooja","Maya","Arjun"};
    g["Aarav"] = {"Neha","Neha1", "Arjun"};
    g["Arjun"] = {"Rahul", "Neha1","Aarav"};
    g["Arjun1"] = {"Maya","Pooja"};
    g["Pooja"] = {"Rahul","Arjun", "Arjun1"};

    
    cout << "-----------------BFS TRAVERSAL OF GRAPH-----------------" << "\n";
    vector<string> input1 = { "Raj","Sunil","Neha","Maya","Sneha","Akash","Aarav","Rahul","Arjun1","Priya","Neha1","Arjun","Pooja"};
    for(auto it : input1){
        bfs(g,it);
        cout << "------------------------------------------" << "\n";
    }
    cout << "\n";
    cout << "-----------------DFS TRAVERSAL OF GRAPH-----------------" << "\n";
    for(auto it : input1){
        dfs(g,it);
    }
}
