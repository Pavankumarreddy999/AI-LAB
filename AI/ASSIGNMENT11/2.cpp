#include<bits/stdc++.h>
using namespace std;

vector<char> letters = {'S','E','N','D','M','O','R','Y'};
vector<int> value(256,-1); 
vector<bool> used(10,false);

bool check(){
    int S = value['S'],E = value['E'],N = value['N'],D = value['D'],M = value['M'],O = value['O'],R = value['R'],Y = value['Y'];

    if(S == 0 || M == 0) return false;

    int send  = 1000*S + 100*E + 10*N + D;
    int more  = 1000*M + 100*O + 10*R + E;
    int money = 10000*M + 1000*O + 100*N + 10*E + Y;

    return money == (send+more);
}

bool solve(int idx){
    if(idx == letters.size()){
        if(check()){
            cout << "Solution:\n";
            for (char c : letters) {
                cout << c << " = " << value[c] << "\n";
            }

            int send  = 1000*value['S'] + 100*value['E'] + 10*value['N'] + value['D'];
            int more  = 1000*value['M'] + 100*value['O'] + 10*value['R'] + value['E'];
            int money = 10000*value['M'] + 1000*value['O'] + 100*value['N'] + 10*value['E'] + value['Y'];

            cout << "\nVerification:\n";
            cout << send << " + " << more << " = " << money << "\n\n";
        }
        return false;
    }

    for(int d = 0;d<=9;d++){
        if(!used[d]){
            value[letters[idx]] = d;
            used[d] = true;

            solve(idx+1);

            value[letters[idx]] = -1;
            used[d] = false;
        }
    }
    return false;
}

int main(){
    solve(0);
    return 0;
}