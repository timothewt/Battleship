#ifndef PROJECT_HEADER_H
#define PROJECT_HEADER_H
#define BOAT_NUMBER 5 // Constant number of boats
#define GRID_HEIGHT 10 // Constant grid height
#define GRID_WIDTH 10 // Constant grid width

// Structures :

// A structure that defines a grid 
typedef struct Grid Grid;
struct Grid {
    char board[GRID_HEIGHT][GRID_WIDTH]; // 2 dimensions array with all the characters defining the grid
    int height; // Height of the grid
    int width; // Width of the grid
};

// Inventory of the player which holds the quantity of each missile
typedef struct Inventory Inventory;
struct Inventory {
    int qtySimple; // Quantity of simple missiles
    int qtyBomb; // Quantity of bomb missiles
    int qtyTactical; // Quantity of tactical missiles
    int qtyArtillery; // Quantity of artillery missiles
};

// Boat defined with its position, size and other properties
typedef struct Boat Boat;
struct Boat {
    int position[2]; // Position of the most top-left part of the boat, {line,column}
    int size; // Length of the boat
    char orientation; // Orientation of the boat, 'V' : vertical ; 'H' : horizontal
    int alive; // Can take 1 or 0 is the boat is alive or not
    char *cells; // Cells of the boat (B or D)
};

#endif //PROJECT_HEADER_H
