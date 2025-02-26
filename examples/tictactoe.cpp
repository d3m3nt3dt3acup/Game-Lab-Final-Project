#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Game board (3x3 grid)
char board[9] = {'1','2','3','4','5','6','7','8','9'};
bool againstComputer = false;

void drawBoard() {
    system("cls"); // Clear console (Windows)
    cout << "\n\n\tTic Tac Toe\n\n";
    cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << endl;
    cout << "     |     |     " << endl << endl;
}

bool checkWin(char player) {
    // Check rows, columns, and diagonals
    for(int i = 0; i < 3; i++) {
        if(board[i*3] == player && board[i*3+1] == player && board[i*3+2] == player) return true;
        if(board[i] == player && board[i+3] == player && board[i+6] == player) return true;
    }
    if(board[0] == player && board[4] == player && board[8] == player) return true;
    if(board[2] == player && board[4] == player && board[6] == player) return true;
    return false;
}

bool checkDraw() {
    for(char c : board) {
        if(c != 'X' && c != 'O') return false;
    }
    return true;
}

void computerMove() {
    srand(time(0));
    int move;
    do {
        move = rand() % 9;
    } while(board[move] == 'X' || board[move] == 'O');
    board[move] = 'O';
}

int main() {
    int choice;
    char currentPlayer = 'X';
    
    cout << "1. Play against computer\n2. 2 Player game\nChoose: ";
    cin >> choice;
    againstComputer = (choice == 1);

    while(true) {
        drawBoard();
        int move;

        if(currentPlayer == 'O' && againstComputer) {
            computerMove();
        } else {
            cout << "Player " << currentPlayer << ", enter position (1-9): ";
            while(!(cin >> move) || move < 1 || move > 9 || board[move-1] == 'X' || board[move-1] == 'O') {
                cin.clear();
                cin.ignore();
                cout << "Invalid move! Try again: ";
            }
            board[move-1] = currentPlayer;
        }

        if(checkWin(currentPlayer)) {
            drawBoard();
            if(currentPlayer == 'O' && againstComputer) {
                cout << "Computer wins!" << endl;
            } else {
                cout << "Player " << currentPlayer << " wins!" << endl;
            }
            break;
        }

        if(checkDraw()) {
            drawBoard();
            cout << "It's a draw!" << endl;
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    cout << "Play again? (y/n): ";
    char replay;
    cin >> replay;
    if(replay == 'y' || replay == 'Y') {
        // Reset board
        for(int i = 0; i < 9; i++) {
            board[i] = '1' + i;
        }
        main();
    }

    return 0;
}