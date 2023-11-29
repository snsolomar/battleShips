#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
const int BOARD_SIZE = 10, FLEET_SIZE=3;
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


void initFleet(Player& p) {
    // populate a players fleet
    // 1. Read ships.txt, read the name and the size
    /*for each line of file
        select the next ship in the array, s
        read the name, s.name
        read the size, s.size
        */
    ifstream shipFile("ships.txt");

    if (!shipFile.is_open()) {
        cout << "Error opening file." << endl;
        exit(1);
    }

    for (int i = 0; i < FLEET_SIZE; i++) {
        Ship s;
        if (shipFile >> s.name >> s.size) {
            s.hitcount = 0;
            p.fleet[i] = s;
        }
        else {
            cout << "Error reading data from file." << endl;
            break;
        }
    }
    
    shipFile.close();
}

void initBoard(Player& p) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            p.board[i][j] = ' '; // Initialize all cells as empty (' ')
        }
    }
}


int main() {
    Player player1, player2;
    
    initFleet(player1);
    initFleet(player2);
    
    initBoard(player1);
    initBoard(player2);

    // Add the main game logic here

    return 0;
}
