#include "header.h"

using namespace std;

int main() {
    Player p1, p2;
    // Initialize the fleet for both players
    initFleet(p1);
    initFleet(p2);
    // Set up the board for both players
    cout << "Setting up the boards...\n";
    boardSetUp(p1, p2);
    cout << "Board setup complete.\n";
    // Display the initial board
    displayBoard(p1.board, p2.board, false);
    // Start the main game loop
    playGame(p1, p2);
    return 0;
}
