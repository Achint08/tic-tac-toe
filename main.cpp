#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<string>
#include <algorithm>

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
    int playFlag = 1, valid_input;
    string play_input;
    cout << "Let's play Tic tac toe." << endl;
    displayRules();
    while(playFlag) {
        newGame(tictac);
        printBoard(tictac);
        do {
            cout << "Do you want to play again? Press Y for Yes and N for No" << endl;
            cin >> play_input;
            transform(play_input.begin(), play_input.end(), play_input.begin(), ::tolower);
            if (play_input == "yes" || play_input == "ye" || play_input == "y") {
                playFlag = 1;
                valid_input = 1;
            } else if (play_input == "no" || play_input == "n") {
                playFlag = 0;
                valid_input = 1;
            } else {
                valid_input = 0;
            }
        } while (!valid_input);
    }
    return 0;
}
