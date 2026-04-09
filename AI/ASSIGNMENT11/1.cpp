#include<bits/stdc++.h>
using namespace std;

#define V 25

vector<string> districts = {
    "Kuchchh",// 0
    "Banaskantha",// 1
    "Patan",// 2
    "Mehsana",// 3
    "Sabarkantha",// 4
    "GandhiNagar",// 5
    "Kheda",// 6
    "Panchmahal",// 7
    "Dahod",// 8
    "Surendranagar",// 9
    "Ahmedabad",// 10
    "Anand",// 11
    "Vadodara",// 12
    "Bharuch",// 13
    "Narmada",// 14
    "Surat", // 15
    "Navsari",// 16
    "Valsad",// 17
    "Dangs", // 18
    "Rajkot", // 19
    "Jamnagar", // 20
    "Porbandar",// 21
    "Junaghad",// 22
    "Amreli", // 23
    "Bhavnagar"// 24
};

//  Check safe using adjacency list
bool isSafe(int v, vector<vector<int>> &graph, vector<int>& color, int c){
    for(int neighbor : graph[v]){
        if(color[neighbor] == c){
            return false;
        }
    }
    return true;
}

bool evaluate(int v, vector<vector<int>> &graph, int m, vector<int>& color){
    if(v == V) return true;

    for(int c = 1; c <= m; c++){
        if(isSafe(v, graph, color, c)){
            color[v] = c;

            if(evaluate(v + 1, graph, m, color)){
                return true;
            }

            color[v] = 0;
        }
    }
    return false;
}

int main(){
   vector<vector<int>> graph = {
    {1, 2, 9, 20},         
    {0, 2, 3, 4},          
    {0, 1, 3, 9}, 
    {1, 2, 4, 5, 9, 10},     
    {1, 3, 5, 6, 7, 8},    
    {3, 4, 6, 10}, 
    {4, 5, 7, 10, 11, 12},
    {4, 6, 8, 12},  
    {4, 7, 12},     
    {0, 2, 3, 10, 19, 23}, 
    {3, 5, 6, 9, 11, 23, 24},
    {6, 10, 12, 13, 23, 24}, 
    {6, 7, 8, 11, 13, 14},  
    {11, 12, 14, 15, 24}, 
    {12, 13, 15, 18},   
    {13, 14, 16, 18},   
    {15, 17, 18},     
    {16, 18},        
    {14, 15, 16, 17},  
    {9, 20, 21, 22, 23},    
    {0, 19, 21},     
    {19, 20, 22},  
    {19, 21, 23},
    {9, 10, 11, 19, 22, 24},
    {10, 11, 13, 23}
};

    for(int m = 1; m <= V; m++){
        vector<int> color(V, 0);

        if(evaluate(0, graph, m, color)){
            cout << "\n===== MAP COLORING SOLUTION =====\n\n";
            cout << "Minimum colors required: " << m << "\n\n";

            map<int, vector<int>> group;

            for(int i = 0; i < V; i++){
                group[color[i]].push_back(i);
            }

            for(auto &p : group){
                cout << "Color " << p.first << " → " << p.second.size() << " nodes\n{ ";
                for(int i = 0;i < p.second.size();i++){
                    cout << p.second[i];
                    if(i != p.second.size() - 1) cout << ", ";
                }
                cout << " }\n\n";
            }
            break;
        }
    }

    return 0;
}