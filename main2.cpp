#include "header.h"

using namespace std;

int main() {
    Player p1, p2;
    // Initialize the fleet for both players
    initFleet(p1);
    initFleet(p2);
    // Set up the board for both players
    boardSetUp(p1, p2);
    // Display the initial board
    displayBoard(p1.board, p2.board);
    return 0;
}
