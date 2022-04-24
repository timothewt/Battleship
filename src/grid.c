#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "structures.h"
#include "grid.h"

void FillGrid(Grid *grid) {
    for (int i = 0; i < grid->height; i++) { // Goes through all the grid 
        for (int j = 0; j < grid->width; j++) {
            grid->board[i][j] = '_';
        }
    }
}

void ShowGrid(Grid grid) {
    for (int k = 1; k <= grid.width; k++) { 
      printf("|%d", k); // Prints columns numbers
    }
    printf("\n");
    for (int i = 0; i < grid.height; i++) {
        for (int j = 0; j < grid.width; j++) {
            printf("|%c", grid.board[i][j]); // Prints the grid cells
        }
        printf("|%d\n", i + 1); // At the end of the line prints the line number
    }
}

void PlaceBoatsRandomly(Boat boats[BOAT_NUMBER], Grid *ships) {
    for (int i = 0; i < BOAT_NUMBER; i++) {
        int cellsAreFree;  // To know if a boat is already where another spawns
        if (rand() % 2) { // Has 50% chance for the boat to be horizontal 
            boats[i].orientation = 'H';
            do {
                cellsAreFree = 1; // Basically, the cells are considered free
                boats[i].position[0] = rand() % GRID_HEIGHT; // Chooses the coordinates randomly from 0 to 9
                boats[i].position[1] = rand() % ((GRID_WIDTH + 1) - boats[i].size);
                for (int j = boats[i].position[1]; j < boats[i].position[1] + boats[i].size; j++) { // Runs through all the cells where the boat is supposed to be placed
                    if (ships->board[boats[i].position[0]][j] ==
                        'B') { // If a boat is on a cell the variable is set to 0 so the while loops again
                        cellsAreFree = 0;
                    }
                }
            } while (!cellsAreFree); // Loops if the cells are not free
        } else { // Same thing but the orientation is vertical
            boats[i].orientation = 'V';
            do {
                cellsAreFree = 1;
                boats[i].position[0] = rand() % ((GRID_HEIGHT + 1) - boats[i].size);
                boats[i].position[1] = rand() % GRID_WIDTH;
                for (int j = boats[i].position[0]; j < boats[i].position[0] + boats[i].size; j++) {
                    if (ships->board[j][boats[i].position[1]] == 'B') {
                        cellsAreFree = 0;
                    }
                }
            } while (!cellsAreFree);
        }
        PlaceBoat(boats[i], ships);
    }
}

void PlaceBoat(Boat boat, Grid *ships) {
    if (boat.orientation == 'H') {
        for (int i = boat.position[1]; i < boat.position[1] + boat.size; i++) { // Runs through the positions of the boat and replaces it with the information in the boat structure
            ships->board[boat.position[0]][i] = boat.cells[i - boat.position[1]];
        }
    } else {
        for (int i = boat.position[0]; i < boat.position[0] + boat.size; i++) {
            ships->board[i][boat.position[1]] = boat.cells[i - boat.position[0]];
        }
    }
}

void PlaceAllBoats(Boat boats[BOAT_NUMBER], Grid *ships) {
    FillGrid(ships);
    for (int i = 0; i < BOAT_NUMBER; i++) { // Runs through all the boats and places them
        PlaceBoat(boats[i], ships);
    }
}

int CheckDirection(Grid *ships, char direction, int x, int y, int length, int boatSize) {
    switch (direction) {
        case 'U': // If the direction is Up
            if (y - length > 0) { // Only checks if the movement doesn't go out of the grid
                for (int i = y - 1; i >= y - length; i--) {
                    if (ships->board[i][x] == 'B' || ships->board[i][x] == 'D') return 0;
                }
                return 1;
            } else {
                return 0;
            }
            break;
        case 'D': // Same thing but the direction is Down
            if (y + length + boatSize <= GRID_HEIGHT) { // Only checks if the movement doesn't go out of the grid
                for (int i = y + boatSize; i < y + boatSize + length; i++) {
                    if (ships->board[i][x] == 'B' || ships->board[i][x] == 'D') return 0;
                }
                return 1;
            } else {
                return 0;
            }
            break;
        case 'L': // Same thing but the direction is Left
            if (x - length > 0) { // Only checks if the movement doesn't go out of the grid
                for (int i = x - 1; i >= x - length; i--) {
                    if (ships->board[y][i] == 'B' || ships->board[y][i] == 'D') return 0;
                }
                return 1;
            } else {
                return 0;
            }
            break;
        case 'R': // Same thing but the direction is Right
            if (x + length + boatSize <= GRID_WIDTH) { // Only checks if the movement doesn't go out of the grid
                for (int i = x + boatSize; i < x + boatSize + length; i++) {
                    if (ships->board[y][i] == 'B' || ships->board[y][i] == 'D') return 0;
                }
                return 1;
            } else {
                return 0;
            }
            break;
        default:
            return 0;
    }
}

int MoveBoat(Boat *boat, Grid *ships, Boat boats[BOAT_NUMBER], int isAlive) {
	
	for (int i = 0; i < 10; i++) { // 10 tries for random movement

		int movement = rand() % 7 - 3; // from -3 to +3;

		if (movement == 0 || !isAlive) return 0; // If there is no movement or the boat is dead returns 0

		char direction;

		if (boat->orientation == 'H') {  // Chooses the direction of the movement according to the orientation
			direction = movement > 0 ? 'R' : 'L'; // Right or Left
		} else {
			direction = movement > 0 ? 'D' : 'U'; // Down or Up
		}

		if (CheckDirection(ships, direction, boat->position[1], boat->position[0], abs(movement), boat->size)) { // If the movement is possible changes the position of the ships to the direction and orientation if not returns 0
			boat->position[0] += (direction == 'D' || direction == 'U') ? movement : 0;
			boat->position[1] += (direction == 'R' || direction == 'L') ? movement : 0;

			PlaceAllBoats(boats, ships); // Places all the boats with new coordinates
			return 1; // Breaks out of the for loop if the movement has been possible
		}

	}

	return 0; // returns 0 if the movement is impossible after 10 tries
}

int IdentifyBoat(Boat boats[BOAT_NUMBER], int coordinates[2]) {
    for (int i = 0; i <= BOAT_NUMBER; i++) { // Goes through all the boat
        if (boats[i].orientation == 'H') { // Checks if the boat is horizontal or vertical
            for (int j = boats[i].position[1];
                 j < boats[i].position[1] + boats[i].size; j++) { // Goes through the boat cells
                if (j == coordinates[1] && boats[i].position[0] == coordinates[0])
                    return i; // If the coordinates corresponds to one on the boat cells return this boat number
            }
        } else { // Same thing but the boat is vertical
            for (int j = boats[i].position[0]; j < boats[i].position[0] + boats[i].size; j++) {
                if (j == coordinates[0] && boats[i].position[1] == coordinates[1]) return i;
            }
        }
    }

    return -1;
}

int CountBoatCells(Grid ships) {
    int boatCells = 0;
    for (int i = 0; i < ships.height; i++) { // Goes through all the grid 
        for (int j = 0; j < ships.width; j++) {
            if (ships.board[i][j] == 'B') { // If there is still at least one 'B' on the board, ships are still alive
                boatCells++;
            }
        }
    }

    return boatCells;
}

int CountBoats(Boat boats[BOAT_NUMBER]) {
    int boatsAlive = 0;
    for (int i = 0; i < BOAT_NUMBER; i++) { // Counts the number of boats of which alive property is true
        boatsAlive += boats[i].alive;
    }

    return boatsAlive;
}

void UpdateBoatCells(Boat *boat, Grid ships) {
    int x, y;
    x = boat->position[1];
    y = boat->position[0];
    if (boat->orientation == 'H') { // Checks for the orientation of the boat
        for (int i = x; i < x + boat->size; i++) { // Goes through all the boat and replaces the value of the cells with what is on the grid
            boat->cells[i - x] = ships.board[y][i];
        }
    } else { // Same thing but the boat is vertical
        for (int i = y; i < y + boat->size; i++) {
            boat->cells[i - y] = ships.board[i][x];
        }
    }
}

void UpdateGrid(Grid *grid, Grid *ships, int a, int b) {
    if (ships->board[a][b] != '_') {
        grid->board[a][b] = 'X';
        ships->board[a][b] = 'D';
    } else {

        grid->board[a][b] = 'O';
    }
}
