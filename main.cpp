#include <bits/stdc++.h>
#include <windows.h>
#include <random>
using namespace std;

char a[6][7];
int turn = 0;

void view (){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int player = 180, computer = 100, none = 240;
    SetConsoleTextAttribute(h, none);
    cout << "|";
    for (int j = 0; j < 7; j++)
        cout << " " << j + 1 << " |";
    cout << endl;
    cout << "|";
    for (int j = 0; j < 7; j++)
        cout << "___|";
    cout << endl;
    for (int i = 0; i < 6; i++){
        SetConsoleTextAttribute(h, none);
        cout << "|";
        for (int j = 0; j < 7; j++){
            if (a[i][j] == 'X'){
                SetConsoleTextAttribute(h, player);
                cout << " " << a[i][j] << " |";
            }
            else if (a[i][j] == 'O'){
                SetConsoleTextAttribute(h, computer);
                cout << " " << a[i][j] << " |";
            }
            else{
                SetConsoleTextAttribute(h, none);
                cout << " " << a[i][j] << " |";
            }
        }
        cout << endl;
    }
}

bool check (){
    char now = 'X';
    if (turn) now = 'O';
    bool finished = false;
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 4; j++){
            if (a[i][j] == a[i][j + 1] and a[i][j] == a[i][j + 2] and a[i][j] == a[i][j + 3] and a[i][j] == now){
                finished = true;
            }
        }
    }
    for (int j = 0; j < 7; j++){
        for (int i = 0; i < 3; i++){
            if (a[i][j] == a[i + 1][j] and a[i][j] == a[i + 2][j] and a[i][j] == a[i + 3][j] and a[i][j] == now){
                finished = true;
            }
        }
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 4; j++){
            if (a[i][j] == a[i + 1][j + 1] and a[i][j] == a[i + 2][j + 2] and a[i][j] == a[i + 3][j + 3] and a[i][j] == now){
                finished = true;
            }
        }
    }
    for (int i = 0; i < 3; i++){
        for (int j = 6; j > 2; j--){
            if (a[i][j] == a[i + 1][j - 1] and a[i][j] == a[i + 2][j - 2] and a[i][j] == a[i + 3][j - 3] and a[i][j] == now){
                finished = true;
            }
        }
    }
    return finished;
}

bool draw (){
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 6; j++)
        if (!a[i][j]) return false;
    return true;
}

bool invalid (int x){
    return a[0][x];
}

void drop (int x){
    char now = 'X';
    if (turn) now = 'O';
    for (int i = 5; i >= 0; i--){
        if (a[i][x] == 0){
            a[i][x] = now;
            return;
        }
    }
}

int colwinning (char b[6][7], char now){
    for (int x = 0; x < 7; x++){
        if (b[0][x]) continue;
        for (int i = 5; i >= 0; i--) if (b[i][x] == 0) {b[i][x] = now; break;}
        for (int j = 0; j < 7; j++){
            for (int i = 0; i < 3; i++){
                if (b[i][j] == b[i + 1][j] and b[i][j] == b[i + 2][j] and b[i][j] == b[i + 3][j] and b[i][j] == now){
                    return x;
                }
            }
        }
        for (int i = 0; i < 6; i++) if (b[i][x]) {b[i][x] = 0; break;}
    }
    return -1;
}

int elsewinning (char b[6][7], char now){
    for (int x = 0; x < 7; x++){
        if (b[0][x]) continue;
        for (int i = 5; i >= 0; i--) if (b[i][x] == 0) {b[i][x] = now; break;}
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 4; j++){
                if (b[i][j] == b[i][j + 1] and b[i][j] == b[i][j + 2] and b[i][j] == b[i][j + 3] and b[i][j] == now){
                    return x;
                }
            }
        }
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 4; j++){
                if (b[i][j] == b[i + 1][j + 1] and b[i][j] == b[i + 2][j + 2] and b[i][j] == b[i + 3][j + 3] and b[i][j] == now){
                    return x;
                }
            }
        }
        for (int i = 0; i < 3; i++){
            for (int j = 6; j > 2; j--){
                if (b[i][j] == b[i + 1][j - 1] and b[i][j] == b[i + 2][j - 2] and b[i][j] == b[i + 3][j - 3] and b[i][j] == now){
                    return x;
                }
            }
        }
        for (int i = 0; i < 6; i++) if (b[i][x]) {b[i][x] = 0; break;}
    }
    return -1;
}

double evaluate (char b[6][7], char now){
    int colw = colwinning (b, now);
    int elsew = elsewinning (b, now);
    if (colw > -1 or elsew > -1) return 1000000000;
    double score = 0, hit = 0;
    for (int j = 0; j < 7; j++)
    for (int i = 5; i >= 0; i--){
        if (b[0][j]) continue;
        int value = 0;
        if (b[i][j] == 0){
            if (i < 5) value += (b[i + 1][j] == now);
            if (i < 5 and j) value += (b[i + 1][j - 1] == now);
            if (i < 5 and j < 6) value += (b[i + 1][j + 1] == now);
            if (j) value += (b[i][j - 1] == now);
            if (j < 6) value += (b[i][j + 1] == now);
            if (i and j) value += (b[i - 1][j - 1] == now);
            if (i and j < 6) value += (b[i - 1][j + 1] == now);
        }
        hit++;
    }
    return score / hit;
}

double minimax (char b[6][7], int depth){
    char now = 'O';
    if (depth & 1) now = 'X';
    if (depth == 6) return evaluate(b, now);
    double res = -1000000000;
    if (depth & 1) res = -res;
    for (int j = 0; j < 7; j++){
        if (b[0][j]) continue;
        for (int i = 5; i >= 0; i--){
            if (b[i][j] == 0){
                b[i][j] = now;
                break;
            }
        }
        if (depth & 1) res = min (res, minimax (b, depth + 1));
        else res = max (res, minimax (b, depth + 1));
        for (int i = 0; i < 6; i++){
            if (b[i][j]){
                b[i][j] = 0;
                break;
            }
        }
    }
    return res;
}

int computer (){
    char b[6][7];
    for (int g = 0; g < 6; g++) for (int h = 0; h < 7; h++) b[g][h] = a[g][h];
    int colw = colwinning (b, 'O');
    int elsew = elsewinning (b, 'O');
    if (colw > -1) return colw + 1;
    if (elsew > -1) return elsew + 1;
    for (int j = 0; j < 7; j++){
        for (int g = 0; g < 6; g++) for (int h = 0; h < 7; h++) b[g][h] = a[g][h];
        if (b[0][j]) continue;
        for (int i = 5; i >= 0; i--) if (b[i][j] == 0) {b[i][j] = 'O'; break;}
        int forced = colwinning(b, 'X');
        if (forced > -1) return forced + 1;
        for (int i = 5; i >= 0; i--) if (b[i][j]) {b[i][j] = 0; break;}
    }
    int cx[] = {0, 1, 2, 3, 4, 5, 6};
    random_shuffle(cx, cx + 7);
    for (int i = 0; i < 5e6; i++) cout << "";
    for (int j = 0; j < 7; j++){
        for (int g = 0; g < 6; g++) for (int h = 0; h < 7; h++) b[g][h] = a[g][h];
        if (b[0][cx[j]]) continue;
        for (int i = 5; i >= 0; i--) if (b[i][cx[j]] == 0) {b[i][cx[j]] = 'O'; break;}
        int prohibited = elsewinning(b, 'X');
        if (prohibited != -1) cx[j] = -1;
    }
    for (int j = 0; j < 5; j++){
        if (a[0][j]) continue;
        bool found = false;
        for (int k = 0; k < 7; k++) if (cx[k] == j) found = true;
        if (!found) continue;
        int toprow0 = 6, toprow1 = 6, toprow2 = 6;
        for (int i = 5; i >= 0; i--) if (a[i][j] == 0) toprow2 = i;
        for (int i = 5; i >= 0; i--) if (a[i][j + 1]) if (a[i][j + 1] == 'X') {toprow1 = i; break;}
        for (int i = 5; i >= 0; i--) if (a[i][j + 2]) if (a[i][j + 2] == 'X') {toprow2 = i; break;}
        if (toprow1 != 6 and toprow1 == toprow2 and toprow0 == toprow1 + 1) return j + 1;
    }
    for (int j = 2; j < 7; j++){
        if (a[0][j]) continue;
        bool found = false;
        for (int k = 0; k < 7; k++) if (cx[k] == j) found = true;
        if (!found) continue;
        int toprow0 = 6, toprow1 = 6, toprow2 = 6;
//        cout << toprow0 << " " << toprow1 << " " << toprow2 << endl;
        for (int i = 5; i >= 0; i--) if (a[i][j] == 0) toprow2 = i;
        for (int i = 5; i >= 0; i--) if (a[i][j - 1]) if (a[i][j - 1] == 'X') {toprow1 = i; break;}
        for (int i = 5; i >= 0; i--) if (a[i][j - 2]) if (a[i][j - 2] == 'X') {toprow2 = i; break;}
        if (toprow1 != 6 and toprow1 == toprow2 and toprow0 == toprow1 + 1) return j + 1;
    }
    int tocol;
    for (int k = 0; k < 7; k++) if (cx[k] != -1) return tocol = cx[k];
    for (int g = 0; g < 6; g++) for (int h = 0; h < 7; h++) b[g][h] = a[g][h];
    double value = -1000000000;
    for (int i = 0; i < 7; i++){
        for (int g = 0; g < 6; g++) for (int h = 0; h < 7; h++) b[g][h] = a[g][h];
        int res = minimax (b, 0);
        if (res > value){
            value = res;
            tocol = i;
        }
    }
    return tocol + 1;
}

int main (){
    while (1){
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 15);
        view();
        SetConsoleTextAttribute(h, 15);
        cout << (turn ? "Computer's" : "Player's") << " Turn" << endl;
        int col;
        if (turn){
            int counter = 0;
            while (counter < 1000){
                counter++;
                col = computer ();
                if (!invalid (col - 1)) break;
            }
            if (counter >= 1000)
            for (int i = 0; i < 7; i++) if (a[0][i] == 0) col = i + 1;
            cout << endl << "Computer played " << col << endl;
        }
        else{
            while (1){
                cin >> col;
                if (!invalid (col - 1)) break;
                else{
                    cout << "Invalid move!" << endl;
                }
            }
        }
        drop (col - 1);
        if (check ()){
            view ();
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 15);
            cout << (!turn ? "Player" : "Computer");
            cout << " is the winner!" << endl;
            cout << (!turn ? "Congratulations!" : "Bad luck!");
            cout << endl << endl;
            return 0;
        }
        if (draw ()){
            cout << "Match drawn!" << endl;
            return 0;
        }
        turn ^= 1;
    }
    return 0;
}
