#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // Include this header for std::stringstream
#include <cctype>

using namespace std;

// Function to print the Tic-Tac-Toe board
void print_board(char board[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2)
                cout << " | ";
        }
        cout << endl;
        if (i < 2)
            cout << "---------" << endl;
    }
}

// Function to add a player's symbol to the board
void addchar(char board[][3], int spot, char playerSymbol) {
    int row = (spot - 1) / 3;
    int col = (spot - 1) % 3;

    if (board[row][col] == '-') {
        board[row][col] = playerSymbol;
        print_board(board);}
    else
    {cout<<"Invalid spot, Try another one :";
     cin>>spot;
     addchar(board, spot, playerSymbol);
    }

}

void updateWinCounts(fstream& file, int& playerxwins, int& playerowins) {
    string line;
    file.open("Save.txt", ios::in);

    if (file.is_open()) {
        playerxwins = -1;
        playerowins = -1;

        while (getline(file, line)) {
            stringstream ss(line);
            int currentNumber = 0;  // To accumulate digits
            bool readingNumber = false;

            char ch;
            while (ss.get(ch)) {
                if (isdigit(ch)) {
                    currentNumber = currentNumber * 10 + (ch - '0');  // Accumulate digits
                    readingNumber = true;
                } else if (readingNumber) {
                    // If we were reading a number and encountered a non-digit, update the appropriate variable
                    if (playerxwins == -1) {
                        playerxwins = currentNumber;
                    } else if (playerowins == -1) {
                        playerowins = currentNumber;
                    }
                    currentNumber = 0;  // Reset for the next number
                    readingNumber = false;
                }
            }

            // Handle the last number in the line
            if (readingNumber) {
                if (playerxwins == -1) {
                    playerxwins = currentNumber;
                } else if (playerowins == -1) {
                    playerowins = currentNumber;
                }
            }
        }

        file.close();

        cout << "Player X has won " << playerxwins << " times" << endl;
        cout << "Player O has won " << playerowins << " times" << endl<<endl;
    } else {
        cout << "Can't open the file for reading." << endl;
    }
}

void saveWinCounts(fstream& file,int playerxwins, int playerowins) {
    file.open("Save.txt", ios::out); //write update
    if (file.is_open())
    {
        file<<"Player X has won "<<playerxwins<<" times"<<endl;
        file<<"Player O has won "<<playerowins<<" times"<<endl;
        file.close();
    }
    else
        cout<<"can't open this file";
}

// Function to check if there's a win
bool checkwin(char board[][3]) {
    // Check rows and columns for a win
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '-')
            return true;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '-')
            return true;
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-')
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '-')
        return true;

    return false;
}

int main() {
    cout << "-------Welcome To Tic Tac Toe Game-------" << endl;
    int spot;
    int playerxwins;
    int playerowins;

    char winner;
    char playAgain;

    fstream save;


    updateWinCounts(save, playerxwins, playerowins);

    cout << "This is the example board " << endl;
    char board_example[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

    print_board(board_example);
    cout<<endl<<endl;
    do {

    char board[3][3] = {{'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'}};

    print_board(board);

    bool check = false;
    char playerSymbol = 'X';

    for (int round = 1; round <= 9; ++round) {
        cout << "Enter the spot you would like to add your character in: ";
        cin >> spot;

        while (spot>9||spot<=0)
        {
            cout << "Invalid move. Try again :";
            cin>> spot ;
        }

        addchar(board, spot, playerSymbol);

        check = checkwin(board);

        if (check)
            break;
        else
            playerSymbol = (playerSymbol == 'X') ? 'O' : 'X';
    }

    if (check)
        cout << "The Winner is " << playerSymbol << endl;
    else
        cout << "The game is a tie" << endl;

    winner=playerSymbol;

    if (winner=='X')
            playerxwins++;
    else if (winner=='O')
            playerowins++;

     cout<<"Do you want to play again (Y/N) :";
     cin>>playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    saveWinCounts(save, playerxwins, playerowins);

    return 0;
}
