#include<bits/stdc++.h>
using namespace std;

string simple_reflex_agent(char loc,int status,vector<int> rooms){
    // rule 1 : if room is dirty ,clean it
    if(status == 0){
        return "clean_it";
    }
    // rule 2 : if room is clean,move based on location
    if(loc == 'A'){
        return "mov_right";
    }else if(loc == 'B' && rooms[2] == 0){
        return "mov_right";   // C is dirty
    }else if(loc == 'B' && rooms[0] == 0){
        return "mov_left";    // A is dirty
    }else{
        return "mov_left";
    }
}

int main(){
    vector<int> rooms(3);
    for(int i=0;i<3;i++){
        cin >> rooms[i];
    } 
    char location;
    cin >> location;
    int cost = 0;

    if (rooms[0] == 1 && rooms[1] == 1 && rooms[2] == 1) {
        cost = 2;  // cost for checking environment
        cout << "ALL ROOMS ARE ALREADY CLEAN\n";
        cout << "TOTAL PERFORMANCE COST : " << cost;
        return 0;
    }

    for(int step=1;step<=8;step++){
        if(rooms[0] == 1 && rooms[1] == 1 && rooms[2] == 1){
            break;
        }
        int idx;
        if(location == 'A') idx = 0;
        else if(location == 'B') idx = 1;
        else idx = 2;

        int percept = rooms[idx];
        string action = simple_reflex_agent(location,percept,rooms);

        cout << "STEP NO :" << step << "|| LOCATION :" << location << "|| STATUS :" 
        << ((percept == 0) ? "DIRTY" : "CLEAN") << "|| ACTION : " << action << "\n";

        if(action == "clean_it"){
            rooms[idx] = 1;
            // for cleaning +5
            cost += 5;
        }
        // for moving +1
        else if(action == "mov_right"){
            if(location == 'A') location = 'B';
            else if(location == 'B' ) location = 'C';
            cost += 1;
        }else if(action == "mov_left"){
            if(location == 'C') location = 'B';
            else if(location == 'B') location = 'A';
            cost += 1;
        }
    }
    cout << "TOTAL PERFORMANCE COST : " << cost ;
}