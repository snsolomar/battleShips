#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
const int BOARD_SIZE = 6, FLEET_SIZE=5;


struct Point {
    int row;
    int col;
};

struct Ship {
    string name; // ships.txt
    int size; // ships.txt
    int hitcount; // updated each time player guesses our location
    // created when fleet is populated, the location points are based on
    // the size of the ship, the super-sipplied starting location and orientation
    vector<Point> location; 
};
struct Player {
    char board[BOARD_SIZE][BOARD_SIZE];
    Ship fleet[FLEET_SIZE];
};

void displayBoards(char playerBoard[][BOARD_SIZE], char enemyBoard[][BOARD_SIZE]) {
    // Print column headers
    cout << "  P1's Board       P2's Board" << endl;
    cout << "  1 2 3 4 5 6     1 2 3 4 5 6" << endl;

    for (int row = 0; row < BOARD_SIZE; row++) {
        // Convert the row index to the corresponding letter (A-F)
        char rowLetter = 'A' + row;

        // Print row letter
        cout << rowLetter << " ";

        // Print player's board
        for (int col = 0; col < BOARD_SIZE; col++) {
            cout << playerBoard[row][col] << " ";
        }

        cout << "    "; // Space between boards

        // Print enemy's board
        for (int col = 0; col < BOARD_SIZE; col++) {
            cout << enemyBoard[row][col] << " ";
        }

        cout << endl; // Move to the next line
    }
}
// void displayBoards(char playerBoard[][BOARD_SIZE], char enemyBoard[][BOARD_SIZE]) 
// {
//     const string SEP = " | ";
//     const string LINE = "------------";
//     const string SPACE = " ";

//     const char A = 'A';
//     const char ROWLABELS[] = {'A', 'B', 'C', 'D', 'E', 'F'};
//     const string LABEL = "ABCDEF";

//     // Top Border
//     cout << LINE << endl;

//     for (int i = 0; i < BOARD_SIZE; i++)
//     {
//         cout << char(A+i);
//         cout << ROWLABELS[i];
        
//         for (int j = 0; i < BOARD_SIZE; j++)
//         {
//             cout << SEP << playerBoard[i][j];
//         }
//         cout << endl << LINE << endl;
//     }

// }





int main() {
    Player player1, player2;
    
    // initFleet(player1);
    // initFleet(player2);
    

    // Initialize player boards with 0 (for testing)
    char player1Board[BOARD_SIZE][BOARD_SIZE] = {0};
    char player2Board[BOARD_SIZE][BOARD_SIZE] = {0};

    // Display the boards for player1 and player2
    displayBoards(player1Board, player2Board);


    return 0;
}
