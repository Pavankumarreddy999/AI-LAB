#include<bits/stdc++.h>
using namespace std;

struct Rule{
    vector<string> premises;
    string conclusion;
};

// FORWARD CHAINING
bool forwardChaining(vector<Rule>& rules,set<string> facts,string goal){
    queue<string> q;
    for (auto f : facts) q.push(f);

    set<string> inferred = facts;

    while(!q.empty()){
        string fact = q.front(); q.pop();
        if(fact == goal) return true;
        for(auto r : rules){
            bool ok = true;
            for(auto p : r.premises){
                if(!inferred.count(p)){
                    ok = false;
                    break;
                }
            }
            if(ok && !inferred.count(r.conclusion)){
                inferred.insert(r.conclusion);
                q.push(r.conclusion);
            }
        }
    }
    return false;
}

//  BACKWARD CHAINING
bool backwardChaining(vector<Rule>& rules, set<string>& facts, string goal){
    if (facts.count(goal)) return true;

    for (auto r : rules){
        if (r.conclusion == goal){
            bool ok = true;

            for (auto p : r.premises){
                if (!backwardChaining(rules, facts, p)) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                facts.insert(goal);
                return true;
            }
        }
    }

    return false;
}

// RESOLUTION
using Clause = set<string>;

bool isComplement(string a, string b) {
    return (a == "~" + b) || (b == "~" + a);
}

vector<Clause> resolve(Clause c1, Clause c2){
    vector<Clause> result;

    for (auto x : c1) {
        for (auto y : c2){

            if (isComplement(x, y)){

                Clause r;

                for (auto e : c1) if (e != x) r.insert(e);
                for (auto e : c2) if (e != y) r.insert(e);

                result.push_back(r);
            }
        }
    }

    return result;
}

bool resolution(set<Clause> KB, set<Clause> query){
    KB.insert(query.begin(), query.end());

    while (true){
        vector<Clause> clauses(KB.begin(), KB.end());
        set<Clause> newSet;

        for (int i = 0; i < clauses.size(); i++){
            for (int j = i + 1; j < clauses.size(); j++){
                auto res = resolve(clauses[i], clauses[j]);

                for (auto r : res){
                    if (r.empty()) return true;
                    newSet.insert(r);
                }
            }
        }

        bool subset = true;
        for (auto c : newSet){
            if (!KB.count(c)){
                subset = false;
                break;
            }
        }

        if (subset) return false;

        KB.insert(newSet.begin(), newSet.end());
    }
}

// MAIN
int main() {
    // FORWARD CHAINING
    cout << "----- Forward Chaining -----\n";

    // (a)
    vector<Rule> FC1 = {
        {{"P"}, "Q"},
        {{"L","M"}, "P"},
        {{"A","B"}, "L"}
    };

    set<string> facts1 = {"A","B","M"};

    cout << "1(a): " << forwardChaining(FC1, facts1, "Q") << endl;

    // (b)
    vector<Rule> FC2 = {
        {{"A"}, "B"},
        {{"B"}, "C"},
        {{"C"}, "D"},
        {{"D","E"}, "F"}
    };
    set<string> facts2 = {"A","E"};

    cout << "1(b): " << forwardChaining(FC2, facts2, "F") << endl;


    // BACKWARD CHAINING
    cout << "\n----- Backward Chaining -----\n";

    // (a)
    vector<Rule> BC1 = {
        {{"P"}, "Q"},
        {{"R"}, "Q"},
        {{"A"}, "P"},
        {{"B"}, "R"}
    };
    set<string> facts3 = {"A","B"};

    cout << "2(a): " << backwardChaining(BC1, facts3, "Q") << endl;

    // (b)
    vector<Rule> BC2 = {
        {{"A"}, "B"},
        {{"B","C"}, "D"},
        {{"E"}, "C"}
    };
    set<string> facts4 = {"A","E"};

    cout << "2(b): " << backwardChaining(BC2, facts4, "D") << endl;


    // RESOLUTION 
    cout << "\n----- Resolution -----\n";

    // (a)
    set<Clause> R1 = {
        {"P","Q"},
        {"~P","R"},
        {"~Q","S"},
        {"~R","S"}
    };
    set<Clause> query1 = {{"~S"}};

    cout << "3(a): " << resolution(R1, query1) << endl;

    // (b)
    set<Clause> R2 = {
        {"~P","Q"},
        {"~Q","R"},
        {"~S","~R"},
        {"P"}
    };
    set<Clause> query2 = {{"~S"}};

    cout << "3(b): " << resolution(R2, query2) << endl;

    return 0;
}