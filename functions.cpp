#include "header.h"

// Displays board with ships during setup, then empty board during gameplay
void displayBoard(char b1[][BOARD_SIZE], char b2[][BOARD_SIZE], bool gameStarted) {
    // Displaying both player boards
    cout << setw(25) << "Player 1's Board " << setw(37) << "Player 2's Board \n";
    // Display row numbers
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << setw(4) << i + 1;
    }
    cout << SPACEBETWEENBOARD << " ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << setw(4) << i + 1;
    }
    cout << endl << setw(LINE.length() + 2) << LINE << SPACEBETWEENBOARD << LINE << endl;

    // Display board contents
    for (int j = 0; j < BOARD_SIZE; j++) {
        cout << char('A' + j);
        for (int x = 0; x < BOARD_SIZE; x++) {
            char displayChar = b1[j][x];
            // Hide unhit ships ('x') during gameplay
            if (gameStarted && displayChar == 'x') {
                displayChar = '0';
            }
            cout << SEP << displayChar;
        }
        cout << SEP << setw(10) << char('A' + j);
        for (int x = 0; x < BOARD_SIZE; x++) {
            char displayChar = b2[j][x];
            // Hide unhit ships ('x') during gameplay
            if (gameStarted && displayChar == 'x') {
                displayChar = '0';
            }
            cout << SEP << displayChar;
        }
        cout << SEP << endl << setw(LINE.length() + 2) << LINE << SPACEBETWEENBOARD << setw(LINE.length()) << LINE << endl;
    }
}

// initializes ships and sets their hitcounts to 0
void initFleet(Player& P) {
    ifstream input("ships.txt");
    if (!input) {
        cout << "Error opening ships.txt" << endl;
        exit(1);
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            P.board[i][j] = '0';
            // Initialize shipBoard
            P.shipBoard[i][j] = -1; 
        }
    }

    for (int i = 0; i < FLEET_SIZE; i++) {
        if (!(input >> P.fleet[i].name >> P.fleet[i].size)) {
            cout << "Error reading ship data from file" << endl;
            exit(1);
        }
        // Initialize fleet hit ocunt to 0
        P.fleet[i].hitcount = 0;
    }
    input.close();
}
// Check if space is occupied
bool spaceOccupied(int row, int col, char orientation, const Player& p1, int shipSize) {
    if (orientation == 'H' || orientation == 'h') {
        for (int i = col; i < col + shipSize; i++) {
            if (i >= BOARD_SIZE || p1.board[row][i] != '0') {
                return true;
            }
        }
    } else if (orientation == 'V' || orientation == 'v') {
        for (int i = row; i < row + shipSize; i++) {
            if (i >= BOARD_SIZE || p1.board[i][col] != '0') {
                return true;
            }
        }
    }
    return false;
}

void getValidShipInfo(int& row, int& col, char& orientation, const Player& p1, int index) {
    bool valid = false;
    while (!valid) {
        cout << "Enter the starting row (A-F) and column (1-6) coordinates of the ship: ";
        char rowInput;
        cin >> rowInput >> col;
        col--; // Adjusting for 0-indexed array

        rowInput = toupper(rowInput);
        row = rowInput - 'A';

        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
            cout << "Invalid row or column coordinate." << endl;
            continue;
        }

        cout << "What orientation do you want your ship to be placed? H(Horizontal) or V(Vertical): ";
        cin >> orientation;

        if (spaceOccupied(row, col, orientation, p1, p1.fleet[index].size)) {
            cout << "Ship placement is taken or out of bounds." << endl;
        } else {
            valid = true;
        }
    }
}
// 
void placeShip(Player& p1, int index) {
    int row, col;
    char ori;
    getValidShipInfo(row, col, ori, p1, index);

    if ((ori == 'H' || ori == 'h') && col + p1.fleet[index].size <= BOARD_SIZE) {
        for (int i = col; i < col + p1.fleet[index].size; i++) {
            p1.board[row][i] = 'x';
            // Set ship index on shipBoard
            p1.shipBoard[row][i] = index;
            p1.fleet[index].positions.push_back({row, i});
        }
    } else if ((ori == 'V' || ori == 'v') && row + p1.fleet[index].size <= BOARD_SIZE) {
        for (int i = row; i < row + p1.fleet[index].size; i++) {
            p1.board[i][col] = 'x';
            // Set ship index on shipBoard
            p1.shipBoard[i][col] = index; 
            p1.fleet[index].positions.push_back({i, col});
        }
    }
}

// initialize board set up
void boardSetUp(Player& p1, Player& p2) {
    for (int i = 0; i < FLEET_SIZE; i++) {
        cout << "Placing ship " << i + 1 << " for Player 1" << endl;
        placeShip(p1, i);
        // Display board after placing each ship for Player 1
        displayBoard(p1.board, p2.board, false); 

        cout << "Placing ship " << i + 1 << " for Player 2" << endl;
        placeShip(p2, i);
        // Display board after placing each ship for Player 2
        displayBoard(p1.board, p2.board, false); 
    }
}
// Displays Board after attack
void updateBoardAfterAttack(Player& attacker, Player& defender) {
    displayBoard(attacker.board, defender.board, true);
}
// Check if hit
void checkIfShipSunk(Player& attacker, Player& defender, int row, int col) {
    // Get the ship index at the hit position
    int shipIndex = defender.shipBoard[row][col]; 
    if (shipIndex == -1) {
        // No ship at this position
        return; 
    }

    defender.fleet[shipIndex].hitcount++; // Increment hit count of the ship

    if (defender.fleet[shipIndex].hitcount == defender.fleet[shipIndex].size) {
        cout << "Ship " << defender.fleet[shipIndex].name << " sunk!" << endl;
        for (int i = 0; i < defender.fleet[shipIndex].positions.size(); ++i) {
            int posRow = defender.fleet[shipIndex].positions[i].row;
            int posCol = defender.fleet[shipIndex].positions[i].column;
            defender.board[posRow][posCol] = 'S'; // Mark 'S' for sunk
        }
        displayBoard(attacker.board, defender.board, true);
    }
}
// allows player to make attack
void makeAttack(Player& attacker, Player& defender) {
    char rowInput;
    int row, col;
    cout << "Enter the attack coordinates (Row A-F, Column 1-6): ";
    cin >> rowInput >> col;
    col--; // Adjust for 0-indexed array

    rowInput = toupper(rowInput);
    row = rowInput - 'A';

    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        cout << "Invalid coordinates. Try again." << endl;
        return makeAttack(attacker, defender);
    }

    if (defender.board[row][col] == 'x') {
        cout << "Hit detected at " << rowInput << col+1 << endl;
        defender.board[row][col] = 'H'; // Mark hit on the board
        //updateBoardAfterAttack(attacker, defender);
        checkIfShipSunk(attacker, defender, row, col);
    } else {
        cout << "Miss." << endl;
        defender.board[row][col] = 'M'; // Mark miss on the board
        //updateBoardAfterAttack(attacker, defender);
        
    }
    displayBoard(attacker.board, defender.board, true);
}


// Checks if the game is over after an attack
bool checkForGameOver(Player& player) {
    // Check if all ships of a player are sunk
    for (int i = 0; i < FLEET_SIZE; i++) {
        // Debugging line
        // cout << "Ship " << player.fleet[i].name << ": hitcount = " << player.fleet[i].hitcount << ", size = " << player.fleet[i].size << endl; 
        // Debugging line
        if (player.fleet[i].hitcount < player.fleet[i].size) {
            cout << "Game is not over, ship " << player.fleet[i].name << " is not sunk." << endl; 
            // Game is not over
            return false; 
        }
    }
    // All ships are sunk
    return true; 
}
// Start the game
void playGame(Player& p1, Player& p2) {
    while (true) {
        cout << "Player 1's turn to attack." << endl;
        makeAttack(p1, p2);
        if (checkForGameOver(p2)) {
            cout << "Player 1 wins!" << endl;
            break;
        }

        cout << "Player 2's turn to attack." << endl;
        makeAttack(p2, p1);
        if (checkForGameOver(p1)) {
            cout << "Player 2 wins!" << endl;
            break;
        }
    }
}
