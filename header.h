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

struct Ship {
    string name;
    int size;
    int hitcount;
    vector<Point> positions;
};

struct Player {
    char board[BOARD_SIZE][BOARD_SIZE];
    Ship fleet[FLEET_SIZE];
    int shipBoard[BOARD_SIZE][BOARD_SIZE];
};

// Function declarations
void displayBoard(char b1[][BOARD_SIZE], char b2[][BOARD_SIZE]);
void initFleet(Player& P);
bool spaceOccupied(int row, int col, char orientation, const Player& p1, int shipSize);
void getValidShipInfo(int& row, int& col, char& orientation, const Player& p1, int index);
void placeShip(Player& p1, int index);
void boardSetUp(Player& p1, Player& p2);


