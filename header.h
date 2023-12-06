#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <iomanip>
#include <cctype>

using namespace std;

const int BOARD_SIZE = 6;
const int FLEET_SIZE = 5;
const string SEP = " | ";
const string LINE = "-------------------------";
const string SPACEBETWEENBOARD = "            "; 

struct Point {
    int row;
    int column;
};
// stores information about each ship
struct Ship {
    string name;
    int size;
    int hitcount;
    // store the positions of each ship
    vector<Point> positions;
};
// represents each player
struct Player {
    char board[BOARD_SIZE][BOARD_SIZE];
    Ship fleet[FLEET_SIZE];
    // Each player has a board
    // 2D array to track which ship occupies which position on the board
    // this is used to find out which ship is hit
    int shipBoard[BOARD_SIZE][BOARD_SIZE];
};

// Function declarations
void displayBoard(char b1[][BOARD_SIZE], char b2[][BOARD_SIZE], bool gameStarted);
void initFleet(Player& P);
bool spaceOccupied(int row, int col, char orientation, const Player& p1, int shipSize);
void getValidShipInfo(int& row, int& col, char& orientation, const Player& p1, int index);
void placeShip(Player& p1, int index);
void boardSetUp(Player& p1, Player& p2);
void checkIfShipSunk(Player& attacker, Player& defender, int row, int col);
void makeAttack(Player& attacker, Player& defender);
bool checkForGameOver(Player& player);
void playGame(Player& p1, Player& p2);


