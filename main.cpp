#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

// ─────────────────────────────────────────────
//  Global Variables
// ─────────────────────────────────────────────
char board[3][3];
int  winsX = 0, winsO = 0, draws = 0;

// ─────────────────────────────────────────────
//  Utility helpers
// ─────────────────────────────────────────────
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\n  Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ─────────────────────────────────────────────
//  Board Functions
// ─────────────────────────────────────────────
void initBoard() {
    int num = 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '0' + num++;
}

void displayBoard() {
    cout << "\n";
    cout << "  ┌───┬───┬───┐\n";
    for (int i = 0; i < 3; i++) {
        cout << "  │";
        for (int j = 0; j < 3; j++) {
            if      (board[i][j] == 'X') cout << " \033[31mX\033[0m │";
            else if (board[i][j] == 'O') cout << " \033[34mO\033[0m │";
            else                         cout << " " << board[i][j] << " │";
        }
        cout << "\n";
        if (i < 2) cout << "  ├───┼───┼───┤\n";
    }
    cout << "  └───┴───┴───┘\n";
}

// ─────────────────────────────────────────────
//  Game Logic
// ─────────────────────────────────────────────
bool checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        // Rows & Columns
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    // Diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

bool checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') return false;
    return true;
}

bool makeMove(char player, int pos) {
    if (pos < 1 || pos > 9) return false;
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;
    if (board[row][col] == 'X' || board[row][col] == 'O') return false;
    board[row][col] = player;
    return true;
}

// ─────────────────────────────────────────────
//  AI Move (Simple: random available cell)
// ─────────────────────────────────────────────
void aiMove() {
    // Try to win
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                board[i][j] = 'O';
                if (checkWin('O')) return;
                board[i][j] = '1' + i * 3 + j;
            }
    // Block player
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                board[i][j] = 'X';
                if (checkWin('X')) { board[i][j] = 'O'; return; }
                board[i][j] = '1' + i * 3 + j;
            }
    // Take center
    if (board[1][1] != 'X' && board[1][1] != 'O') { board[1][1] = 'O'; return; }
    // Random
    int available[9], count = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                available[count++] = i * 3 + j;
    if (count > 0) {
        int pick = available[rand() % count];
        board[pick / 3][pick % 3] = 'O';
    }
}

// ─────────────────────────────────────────────
//  GAME MODES
// ─────────────────────────────────────────────
void twoPlayerGame() {
    initBoard();
    char current = 'X';
    string p1, p2;

    clearScreen();
    cout << "\n  ╔══════════════════════════════════════════╗\n";
    cout << "  ║           TWO PLAYER MODE                ║\n";
    cout << "  ╚══════════════════════════════════════════╝\n\n";
    cout << "  Player 1 Name (X): "; cin >> p1;
    cout << "  Player 2 Name (O): "; cin >> p2;

    for (int moves = 0; moves < 9; moves++) {
        clearScreen();
        cout << "\n  Score → " << p1 << ": " << winsX
             << "  |  " << p2 << ": " << winsO
             << "  |  Draws: " << draws << "\n";

        displayBoard();
        string curName = (current == 'X') ? p1 : p2;
        cout << "\n  " << curName << "'s turn (" << current << "). Enter position (1-9): ";

        int pos;
        while (!(cin >> pos) || !makeMove(current, pos)) {
            cout << "  Invalid! Enter a valid position (1-9): ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (checkWin(current)) {
            clearScreen();
            displayBoard();
            cout << "\n  🎉  " << curName << " (" << current << ") WINS!\n";
            if (current == 'X') winsX++; else winsO++;
            pause(); return;
        }
        if (checkDraw()) {
            clearScreen();
            displayBoard();
            cout << "\n  🤝  It's a DRAW!\n";
            draws++;
            pause(); return;
        }
        current = (current == 'X') ? 'O' : 'X';
    }
}

void vsAIGame() {
    srand(time(0));
    initBoard();

    clearScreen();
    cout << "\n  ╔══════════════════════════════════════════╗\n";
    cout << "  ║         PLAYER VS AI MODE                ║\n";
    cout << "  ╚══════════════════════════════════════════╝\n\n";
    cout << "  Your Name: ";
    string player; cin >> player;
    cout << "\n  You are X. AI is O.\n";
    pause();

    for (int moves = 0; moves < 9; moves++) {
        clearScreen();
        cout << "\n  Score → You: " << winsX
             << "  |  AI: " << winsO
             << "  |  Draws: " << draws << "\n";
        displayBoard();

        if (moves % 2 == 0) {
            // Player turn
            cout << "\n  Your turn (X). Enter position (1-9): ";
            int pos;
            while (!(cin >> pos) || !makeMove('X', pos)) {
                cout << "  Invalid! Enter a valid position (1-9): ";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (checkWin('X')) {
                clearScreen(); displayBoard();
                cout << "\n  🎉  " << player << " WINS! You beat the AI!\n";
                winsX++; pause(); return;
            }
        } else {
            // AI turn
            cout << "\n  AI is thinking...\n";
            aiMove();
            if (checkWin('O')) {
                clearScreen(); displayBoard();
                cout << "\n  🤖  AI WINS! Better luck next time.\n";
                winsO++; pause(); return;
            }
        }

        if (checkDraw()) {
            clearScreen(); displayBoard();
            cout << "\n  🤝  It's a DRAW!\n";
            draws++; pause(); return;
        }
    }
}

// ─────────────────────────────────────────────
//  MAIN MENU
// ─────────────────────────────────────────────
void showMenu() {
    clearScreen();
    cout << "\n  ╔══════════════════════════════════════════╗\n";
    cout << "  ║       TIC TAC TOE - MINI GAME            ║\n";
    cout << "  ╚══════════════════════════════════════════╝\n\n";
    cout << "  📊  Scoreboard → X: " << winsX
         << "  O: " << winsO
         << "  Draws: " << draws << "\n\n";
    cout << "       1.  Two Player Mode\n";
    cout << "       2.  Player vs AI\n";
    cout << "       3.  Reset Scores\n";
    cout << "       4.  Exit\n\n";
    cout << "  Enter your choice: ";
}

int main() {
    int choice;
    do {
        showMenu();
        while (!(cin >> choice)) {
            cout << "  Invalid input. Enter a number: ";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: {
                char replay;
                do {
                    twoPlayerGame();
                    cout << "\n  Play again? (y/n): "; cin >> replay;
                } while (replay == 'y' || replay == 'Y');
                break;
            }
            case 2: {
                char replay;
                do {
                    vsAIGame();
                    cout << "\n  Play again? (y/n): "; cin >> replay;
                } while (replay == 'y' || replay == 'Y');
                break;
            }
            case 3:
                winsX = winsO = draws = 0;
                cout << "\n  ✔  Scores reset!\n";
                pause();
                break;
            case 4:
                clearScreen();
                cout << "\n  Thanks for playing! Goodbye!\n\n";
                break;
            default:
                cout << "\n  ✖  Invalid choice! Enter 1-4.\n";
                pause();
        }
    } while (choice != 4);
    return 0;
}
