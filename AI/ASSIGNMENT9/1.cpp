#include <bits/stdc++.h>
using namespace std;

char board[3][3];
int nodesVisited = 0;

// Print board with prefix (tree structure)
void printBoard(string prefix) {
    for(int i=0;i<3;i++){
        cout << prefix;
        for(int j=0;j<3;j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << prefix << "---------\n";
}

// Evaluation
int evaluate() {
    for(int i=0;i<3;i++){
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!='_')
            return (board[i][0]=='X') ? 10 : -10;
    }

    for(int j=0;j<3;j++){
        if(board[0][j]==board[1][j] && board[1][j]==board[2][j] && board[0][j]!='_')
            return (board[0][j]=='X') ? 10 : -10;
    }

    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!='_')
        return (board[0][0]=='X') ? 10 : -10;

    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!='_')
        return (board[0][2]=='X') ? 10 : -10;

    return 0;
}

bool isMovesLeft() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]=='_') return true;
    return false;
}

// Minimax with TREE visualization
int minimax(bool isMax, string prefix) {
    nodesVisited++;

    int score = evaluate();

    if(score==10 || score==-10 || !isMovesLeft()){
        printBoard(prefix);
        return score;
    }

    if(isMax){
        int best = -1000;

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]=='_'){

                    board[i][j] = 'X';

                    cout << prefix << "├── X(" << i << "," << j << ")\n";
                    printBoard(prefix + "│   ");

                    best = max(best, minimax(false, prefix + "│   "));

                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
    else{
        int best = 1000;

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]=='_'){

                    board[i][j] = 'O';

                    cout << prefix << "├── O(" << i << "," << j << ")\n";
                    printBoard(prefix + "│   ");

                    best = min(best, minimax(true, prefix + "│   "));

                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

// Find best move
pair<int,int> findBestMove() {

    int bestVal = -1000;
    pair<int,int> bestMove = {-1,-1};

    cout << "ROOT\n";
    printBoard("");

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]=='_'){

                board[i][j] = 'X';

                cout << "├── X(" << i << "," << j << ")\n";
                printBoard("│   ");

                int moveVal = minimax(false, "│   ");

                board[i][j] = '_';

                if(moveVal > bestVal){
                    bestMove = {i,j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

int main() {
    char init[3][3] = {
        {'X','O','X'},
        {'O','O','_'},
        {'_','_','_'}
    };

    memcpy(board, init, sizeof(board));

    pair<int,int> best = findBestMove();

    cout << "\nBest Move: (" << best.first << "," << best.second << ")\n";
    cout << "Nodes Visited: " << nodesVisited << endl;

    return 0;
}