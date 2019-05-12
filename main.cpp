#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef vector<vector<char>> board;  //array of array of characters

void newGame(board &tictac) {
    for(int i = 0; i < 5; i++) {
        tictac[i].resize(5);
        for(int j = 0; j < 5; j++) {
            if(i % 2 != 0) {
                    tictac[i][j] = (j % 2 == 0) ? '-' : ' ';
            } else {
                tictac[i][j] = (j % 2 == 0) ? ' ' : '|';
            }
        }
    }
}

void printBoard(board &tictac) {
    for (int i = 0; i < 5; i ++) {
        for(int j = 0; j < 5; j++) {
            cout << tictac[i][j];
        }
        cout << endl;
    }
}

void displayRules() {
    board rules_board(5);
    for (int i = 0; i < 5; i++) {
        rules_board[i].resize(5);
        for (int j = 0; j < 5; j++) {
            if (i % 2 != 0) {
                rules_board[i][j] = (j % 2 == 0) ? '-' : ' ';
            } else {
                rules_board[i][j] = (j % 2 == 0) ? 3 * (i/2) + (j / 2) + 1 + '0' : '|';
            }
        }

    }
    printBoard(rules_board);
    cout << "Use keys from 1 - 9" << endl;
}

int main() {
    srand(time(NULL));
    board tictac(5);
    int playFlag = 1;
    cout << "Let's play Tic tac toe." << endl;
    displayRules();
    while(playFlag) {
        newGame(tictac);
        printBoard(tictac);
        playFlag = 0;

    }
    return 0;
}
