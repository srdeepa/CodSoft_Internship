#include <iostream>
#include <vector>

using namespace std;

char board[3][3];
char currentPlayer;

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard() {
    cout << "\nCurrent Board:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------\n";
    }
    cout << endl;
}

bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
            return true;
        }
    }
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
        return true;
    }
    return false;
}

bool checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void makeMove() {
    int row, col;
    cout << "Player " << currentPlayer << ", enter your move (row and column): ";
    cin >> row >> col;

    if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
        cout << "Invalid move. Try again.\n";
        makeMove();  // Recursively prompt for a valid move
    } else {
        board[row - 1][col - 1] = currentPlayer;
    }
}

int main() {
    char playAgain;

    do {
        initializeBoard();
        currentPlayer = 'X';

        while (true) {
            displayBoard();
            makeMove();

            if (checkWin()) {
                displayBoard();
                cout << "Player " << currentPlayer << " wins!\n";
                break;
            }
            if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!\n";
                break;
            }
            switchPlayer();
        }

        cout << "Do you want to play again? (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

    cout << "Thank you for playing!\n";
    return 0;
}

//OUTPUT
/*
Current Board:
  |   |  
---------
  |   |  
---------
  |   |  

Player X, enter your move (row and column): 2 3

Current Board:
  |   |  
---------
  |   | X
---------
  |   |  

Player O, enter your move (row and column): 2 2

Current Board:
  |   |  
---------
  | O | X
---------
  |   |  

Player X, enter your move (row and column): 1 2

Current Board:
  | X |  
---------
  | O | X
---------
  |   |  

Player O, enter your move (row and column): 1 1 

Current Board:
O | X |  
---------
  | O | X
---------
  |   |  

Player X, enter your move (row and column): 2 1

Current Board:
O | X |  
---------
X | O | X
---------
  |   |  

Player O, enter your move (row and column): 3 3

Current Board:
O | X |  
---------
X | O | X
---------
  |   | O

Player O wins!
Do you want to play again? (Y/N): N
Thank you for playing!
  */
