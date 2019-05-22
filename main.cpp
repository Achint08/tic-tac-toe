#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<string>
#include <algorithm>
#include <climits>

using namespace std;

typedef vector<vector<char> > board;  //array of array of characters

typedef int x_cord;
typedef int y_cord;
typedef int value;
typedef int turn;
typedef int depth;
typedef vector<string> playerName;
typedef vector<bool> isUsed;
typedef vector<pair<x_cord, y_cord> > position_map;
typedef char mode;
typedef int score;

void printBoard(board &tictac) {


    for (x_cord i = 0; i < 5; i++) {
        for (y_cord j = 0; j < 5; j++) {
            cout << tictac[i][j];
        }
        cout << endl;
    }
    cout << endl << endl;
}


turn boardCheck(board &tictac, position_map pm) {
    char pos_char;
    turn p = -1;
    //Horizontal win check: Pattern 123, 456, 789
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

    //Vertical Win check: Pattern 147, 258, 369
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
    //Diagonal Win check: Pattern 159
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

    //Diagonal Win check: Pattern 357
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

score calcScore(board tictac, isUsed iu, position_map pm, depth d, turn t) {
    score s, max_score = INT_MIN, min_score = INT_MAX;
    turn win = boardCheck(tictac, pm);
    if (win == 2) {
        return (10 - d);
    } else if (win == 1) {
        return (-10 + d);
    }
    for (value i = 1; i <= 9; i++) {
        if (!iu[i - 1]) {
            iu[i - 1] = true;
            tictac[pm[i - 1].first][pm[i - 1].second] = (t == 1) ? 'X' : 'O';
            s = calcScore(tictac, iu, pm, d + 1, t % 2 + 1);
            iu[i - 1] = false;
            tictac[pm[i - 1].first][pm[i - 1].second] = ' ';
            if (s < min_score && t == 1) {
                min_score = s;
            }
            if (s > max_score && t == 2) {
                max_score = s;
            }
        } else {

        }
    }
    if (t == 1) {
        return min_score;
    } else {
        return max_score;
    }
}

//Computer AI Movement through minmax algorithm
// TO-DO: Alpha beta pruning
value autoMove(board tictac, isUsed iu, position_map pm) {
    score s, max_score = INT_MIN;
    value move;
    turn t = 2;
    for (value i = 1; i <= 9; i++) {
        if (!iu[i - 1]) {
            iu[i - 1] = true;
            tictac[pm[i - 1].first][pm[i - 1].second] = 'O';
            s = calcScore(tictac, iu, pm, 0, t % 2 + 1);
            iu[i - 1] = false;
            tictac[pm[i - 1].first][pm[i - 1].second] = ' ';
            if (s > max_score) {
                max_score = s;
                move = i;
            }
        }
    }
    return move;
}

void startGame(board &tictac, playerName p, position_map pm, mode m) {
    turn t;
    turn win;
    value v;
    x_cord x;
    y_cord y;
    int i = 0;
    isUsed iu(9, false);
    cout << "----------------- Let's play Tic tac toe. ----------------- " << endl;
    if(rand() % 2 == 0) {
        t = 1;
    } else {
        t = 2;
    }
    cout << p[t - 1] << "'s turn first" << endl;
    while(i < 9) {
        cout << "Choose number for move: " << p[t - 1] << "'s turn" << endl;
        if (m == 'c' && t == 2) {
            v = autoMove(tictac, iu, pm);
        } else {
            cin >> v;
        }

        if (iu[v - 1] == true) {
            cout << "Oops!! Place already occupied" << endl;
            continue;
        }
        if(v < 1 || v > 9) {
            cout << p[t - 1] << ": Choose between 1 and 9. All okay, bro?" << endl;
            continue;
        }
        x = pm[v - 1].first;
        y = pm[v - 1].second;
        tictac[x][y] = (t == 1) ? 'X' : 'O';
        printBoard(tictac);
        win = boardCheck(tictac, pm);
        if(win == 1 || win == 2) {
            cout << p[win - 1] << " wins" << endl;
            break;
        }
        if(i == 8 && win == -1) {
            cout << "Match Draw" << endl;
        }
        iu[v - 1] = true;
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

void setupDisplayRules(position_map &pm) {
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

void setPlayerName(playerName &p, mode m) {
    p.resize(2);
    string s;
    int human_players;
    if (m == 'c') {
        p[1] = "Computer";
        human_players = 1;
    } else {
        human_players = 2;
    }
    for (int i = 0; i < human_players; i++) {
        cout << "Set Player " << i + 1 << " Name"<< endl << endl;
        cin >> s;
        p[i] = s;
    }

}

int main() {
    srand(time(NULL));
    board tictac(5);
    position_map pm;
    playerName p;
    mode m;
    int playFlag = 1, valid_input;
    string play_input;
    do {
        cout << "Press M for Multiplayer mode or  C for (Clash with Computer) mode?" << endl;
        cin >> m;
        m = tolower(m);
        if (m == 'm' || m == 'c') {
            setPlayerName(p, m);
        }
    } while (m != 'm' && m != 'c');
    setupDisplayRules(pm);
    while(playFlag) {
        newGame(tictac);
        cout << endl;
        do {
            cout << "Ready to play? Press Y for Yes and N for No" << endl;
            cin >> play_input;
            transform(play_input.begin(), play_input.end(), play_input.begin(), ::tolower);
            if (play_input == "yes" || play_input == "ye" || play_input == "y") {
                playFlag = 1;
                valid_input = 1;
                startGame(tictac, p, pm, m);
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
