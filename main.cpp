#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<string>
#include <algorithm>
#include <map>

using namespace std;

typedef vector<vector<char> > board;  //array of array of characters

typedef int x_cord;
typedef int y_cord;
typedef int value;
typedef int turn;
typedef vector<bool> isUsed;
typedef vector<pair<x_cord, y_cord>> position_map;
position_map pm(9);


//TO-DO
turn boardCheck(board &tictac) {
    return -1;
}


void printBoard(board &tictac) {


    for (x_cord i = 0; i < 5; i ++) {
        for(y_cord j = 0; j < 5; j++) {
            cout << tictac[i][j];
        }
        cout << endl;
    }
}

void startGame(board &tictac){
    turn t;
    turn win;
    value v;
    x_cord x;
    y_cord y;
    int i = 0;
    isUsed iu(false, 9);
    cout << "Let's play tic tac toe" << endl;
    if(rand() % 2 == 0) {
        t = 1;
        cout << "Player 1 turn first" << endl;
    } else {
        t = 2;
        cout << "Player 1 turn first" << endl;
    }
    while(i < 9) {
        cout << "Choose number for move: Player " << t << "turn" << endl;
        cin >> v;
        if(iu[v] == true) {
            cout << "Oops!! Place already occupied" << endl;
            continue;
        }
        x = pm[v].first;
        y = pm[v].second;
        tictac[x][y] = (t == 0) ? 'X' : 'O';
        printBoard(tictac);
        win = boardCheck(tictac);
        if(win == 0 || win == 1) {
            cout << "Player" << win << "wins" << endl;
            break;
        }
        iu[v] = true;
        i++;
        //change the turn
        t = (t + 1) % 2;
    }
}

void newGame(board &tictac) {
    for(x_cord i = 0; i < 5; i++) {
        tictac[i].resize(5);
        for(y_cord j = 0; j < 5; j++) {
            tictac[i][j] =  (i % 2 != 0) ? ((j % 2 == 0) ? '-' : ' ') : ((j % 2 == 0) ? ' ' : '|');
        }
    }
}

void setupDisplayRules() {
    board rules_board(5);

    for (x_cord i = 0; i < 5; i++) {
        rules_board[i].resize(5);
        for (y_cord j = 0; j < 5; j++) {
            if (i % 2 != 0) {
                rules_board[i][j] = (j % 2 == 0) ? '-' : ' ';
            } else {
                rules_board[i][j] = (j % 2 == 0) ? 3 * (i/2) + (j / 2) + 1 + '0' : '|';
                if(j % 2 == 0) {
                    pm.push_back(pair<x_cord, y_cord>(i, j));
                }
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
    while(playFlag) {
        newGame(tictac);
        printBoard(tictac);
        cout << "Let's play Tic tac toe." << endl;
        setupDisplayRules();
        do {
            cout << "Do you want to play again? Press Y for Yes and N for No" << endl;
            cin >> play_input;
            transform(play_input.begin(), play_input.end(), play_input.begin(), ::tolower);
            if (play_input == "yes" || play_input == "ye" || play_input == "y") {
                playFlag = 1;
                valid_input = 1;
                startGame(tictac);
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
