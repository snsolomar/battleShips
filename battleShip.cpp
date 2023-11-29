#include <iostream>
#include <vector>
using namespace std;

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

int main() {
    return 0;
}
