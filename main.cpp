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
position_map pm;


//TO-DO
turn boardCheck(board &tictac) {
    char pos_char;
    turn p = -1;
    //Horizontal win check
    for(value i = 1; i <= 7; i += 3) {
        pos_char = tictac[pm[i - 1].first][pm[i - 1].second];
        for(value j = i + 1; j <= i + 2; j++) {
            if(tictac[pm[j - 1].first][pm[j - 1].second] != pos_char) {
                p = -1;
                break;
            } else if(tictac[pm[j - 1].first][pm[j - 1].second] == pos_char) {
                if(pos_char == 'X') {
                    p = 1;
                    if(j == i + 2) {
                        break;
                    }
                } else if (pos_char == 'O'){
                    p = 2;
                    if(j == i + 2) {
                        break;
                    }
                }
            }
        }
        if(p != -1) {
            return p;
        }
    }

    //Vertical Win check
    for(value i = 1; i <= 3; i ++) {
        pos_char = tictac[pm[i - 1].first][pm[i - 1].second];
        for(value j = i + 3; j <= i + 6; j+= 3) {
            if(tictac[pm[j - 1].first][pm[j - 1].second] != pos_char || tictac[pm[j - 1].first][pm[j - 1].second] == ' ') {
                p = -1;
                break;
            } else if(tictac[pm[j - 1].first][pm[j - 1].second] == pos_char) {
                if(pos_char == 'X') {
                    p = 1;
                    if(j == i + 6) {
                        break;
                    }
                } else if (pos_char == 'O') {
                    p = 2;
                    if(j == i + 6) {
                        break;
                    }
                }
            }
        }
        if(p != -1) {
            return  p;
        }
    }
    //Diagonal Win check
    pos_char = tictac[pm[0].first][pm[0].second];
    for(value j = 5; j <= 9; j+= 4) {
        if(tictac[pm[j - 1].first][pm[j - 1].second] != pos_char) {
            p = -1;
            break;
        } else if(tictac[pm[j - 1].first][pm[j - 1].second] == pos_char) {
            if(pos_char == 'X') {
                p = 1;
                if(j == 9) {
                    break;
                }
            } else if (pos_char == 'O') {
                p = 2;
                if(j == 9) {
                    break;
                }
            }
        }
    }

    if( p != -1) {
        return p;
    }

    pos_char = tictac[pm[2].first][pm[2].second];
    for(value j = 5; j <= 7; j+= 2) {
        if(tictac[pm[j - 1].first][pm[j - 1].second] != pos_char) {
            p = -1;
            break;
        } else if(tictac[pm[j - 1].first][pm[j - 1].second] == pos_char) {
            if(pos_char == 'X') {
                p = 1;
                if(j == 7) {
                    break;
                }
            } else if (pos_char == 'O') {
                p = 2;
                if(j == 7) {
                    break;
                }

            }
        }
    }
    return p;
}


void printBoard(board &tictac) {


    for (x_cord i = 0; i < 5; i ++) {
        for(y_cord j = 0; j < 5; j++) {
            cout << tictac[i][j];
        }
        cout << endl;
    }
    cout << endl << endl;
}

void startGame(board &tictac){
    turn t;
    turn win;
    value v;
    x_cord x;
    y_cord y;
    int i = 0;
    isUsed iu(9, false);
    cout << "Let's play tic tac toe" << endl;
    if(rand() % 2 == 0) {
        t = 1;
        cout << "Player 1 turn first" << endl;
    } else {
        t = 2;
        cout << "Player 2 turn first" << endl;
    }
    while(i < 9) {
        cout << "Choose number for move: Player " << t << " turn" << endl;
        cin >> v;
        if(iu[v] == true) {
            cout << "Oops!! Place already occupied" << endl;
            continue;
        }
        x = pm[v -1].first;
        y = pm[v - 1].second;
        tictac[x][y] = (t == 1) ? 'X' : 'O';
        printBoard(tictac);
        win = boardCheck(tictac);
        if(win == 1 || win == 2) {
            cout << "Player " << win << " wins" << endl;
            break;
        }
        iu[v] = true;
        i++;
        //change the turn
        t = t % 2 + 1;
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
    cout << "RULES" << endl << endl;
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
    cout << "Use keys from 1 - 9" << endl << endl;
    printBoard(rules_board);
}

int main() {
    srand(time(NULL));
    board tictac(5);
    int playFlag = 1, valid_input;
    string play_input;
    while(playFlag) {
        newGame(tictac);
        cout << endl;
        cout << "----------------- Let's play Tic tac toe. ----------------- " << endl;
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
