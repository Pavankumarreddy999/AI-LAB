#include<bits/stdc++.h>
using namespace std;

const int N = 8;

struct Result{
    int initialH, finalH, steps;
    bool solved;
};

int heuristic(const vector<int>& board){
    int h = 0;
    for(int i=0;i<N;i++)
        for(int j=i+1;j<N;j++){
            if(board[i]==board[j]) h++;
            if(abs(board[i]-board[j])==abs(i-j)) h++;
        }
    return h;
}

vector<int> randomBoard(){
    vector<int> b(N);
    for(int i=0;i<N;i++)
        b[i]=rand()%N;
    return b;
}

Result steepestHC(vector<int> board){
    int initialH = heuristic(board);
    int steps = 0;

    while(true){
        int currH = heuristic(board);
        if(currH==0)
            return {initialH, 0, steps, true};

        int bestH = currH;
        vector<vector<int>> bestBoards;

        for(int c=0;c<N;c++){
            for(int r=0;r<N;r++){
                if(board[c]==r) continue;

                vector<int> nb = board;
                nb[c]=r;
                int h = heuristic(nb);

                if(h<bestH){
                    bestH=h;
                    bestBoards.clear();
                    bestBoards.push_back(nb);
                }
                else if(h==bestH)
                    bestBoards.push_back(nb);
            }
        }

        if(bestH>=currH)
            return {initialH, currH, steps, false};

        board = bestBoards[rand()%bestBoards.size()];
        steps++;
    }
}

Result firstChoiceHC(vector<int> board){
    int initialH = heuristic(board);
    int steps = 0;

    while(true){
        int currH = heuristic(board);
        if(currH==0)
            return {initialH, 0, steps, true};

        bool moved=false;

        for(int tries=0; tries<100; tries++){
            int c = rand()%N;
            int r = rand()%N;
            if(board[c]==r) continue;

            vector<int> nb = board;
            nb[c]=r;

            if(heuristic(nb)<currH){
                board=nb;
                moved=true;
                steps++;
                break;
            }
        }

        if(!moved)
            return {initialH, currH, steps, false};
    }
}

Result randomRestartHC(){
    int totalSteps = 0;

    for(int restart=0; restart<100; restart++){
        vector<int> board = randomBoard();
        Result r = steepestHC(board);
        totalSteps += r.steps;

        if(r.solved)
            return {r.initialH, 0, totalSteps, true};
    }
    return {0, 0, totalSteps, false};
}

Result simulatedAnnealing(vector<int> board){
    int initialH = heuristic(board);
    int steps = 0;

    double T = 1000.0;
    double cooling = 0.99;

    while(T > 0.1){
        int currH = heuristic(board);
        if(currH==0)
            return {initialH, 0, steps, true};

        int c = rand()%N;
        int r = rand()%N;
        if(board[c]==r) continue;

        vector<int> nb = board;
        nb[c]=r;

        int newH = heuristic(nb);
        int delta = newH - currH;

        if(delta < 0){
            board = nb;
        }
        else{
            double prob = exp(-delta/T);
            if(((double)rand()/RAND_MAX) < prob)
                board = nb;
        }

        T *= cooling;
        steps++;
    }

    return {initialH, heuristic(board), steps, false};
}

void runExperiment(string name, int runs){
    cout << "\n========== " << name << " ==========\n";
    cout << setw(4) << "#" 
         << setw(10) << "InitH" 
         << setw(10) << "FinalH"
         << setw(8) << "Steps"
         << setw(10) << "Status\n";
    cout << string(42,'-') << "\n";

    int success=0;

    for(int i=0;i<runs;i++){
        Result r;

        if(name=="Steepest")
            r = steepestHC(randomBoard());
        else if(name=="FirstChoice")
            r = firstChoiceHC(randomBoard());
        else if(name=="RandomRestart")
            r = randomRestartHC();
        else
            r = simulatedAnnealing(randomBoard());

        cout << setw(4) << i+1
             << setw(10) << r.initialH
             << setw(10) << r.finalH
             << setw(8) << r.steps
             << setw(10) << (r.solved?"Solved":"Fail")
             << "\n";

        if(r.solved) success++;
    }

    cout << "\nSuccess: " << success
         << "  Failure: " << runs-success
         << "  Success Rate: "
         << (success*100.0/runs) << "%\n";
}

int main(){
    srand(time(0));

    int runs = 50;

    runExperiment("Steepest", runs);
    runExperiment("FirstChoice", runs);
    runExperiment("RandomRestart", runs);
    runExperiment("SimulatedAnnealing", runs);

    return 0;
}