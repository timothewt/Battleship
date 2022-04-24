#include <stdio.h>
#include "structures.h"
#include "missiles.h"
#include "grid.h"

int CheckQty(int *missileQty) {
    if (*missileQty > 0) {
        return 1;
    } else {
        return 0;
    }
}

int PickMissile(Inventory *inventory, char missileType) {
    switch (missileType) {
        case 'S':
        case 's':
            return CheckQty(&inventory->qtySimple);
            break;
        case 'A':
        case 'a':
            return CheckQty(&inventory->qtyArtillery);
            break;
        case 'B':
        case 'b':
            return CheckQty(&inventory->qtyBomb);
            break;
        case 'T':
        case 't':
            return CheckQty(&inventory->qtyTactical);
            break;
        default:
            printf("An error has occured while picking the missile.\n");
            return 0;
    }
}

void FireSimple(Grid *grid, Grid *ships, int impactPoint[2], Inventory *inventory) {
    UpdateGrid(grid, ships, impactPoint[0], impactPoint[1]);
    (inventory->qtySimple)--;
}

void FireArtillery(Grid *grid, Grid *ships, int impactPoint[2], Inventory *inventory) {
    for (int i = 0; i < GRID_HEIGHT; i++) { // Shooting the whole column
        UpdateGrid(grid, ships, i, impactPoint[1]);
    }
    for (int i = 0; i < GRID_WIDTH; i++) { // Shooting the whole line
        UpdateGrid(grid, ships, impactPoint[0], i);
    }
    (inventory->qtyArtillery)--;
}

void FireBomb(Grid *grid, Grid *ships, int impactPoint[2], Inventory* inventory) {
    for (int i = impactPoint[0] - 2; i < impactPoint[0] + 3; i++) { // Shooting the vertical part
        if (i >= 0 && i < GRID_HEIGHT) { // Verification to know if the cell number is correct
            UpdateGrid(grid, ships, i, impactPoint[1]);
        }
    }

    for (int i = impactPoint[1] - 2; i < impactPoint[1] + 3; i++) { // Shooting the horizontal part
        if (i >= 0 && i < GRID_WIDTH) { // Verification to know if the cell number is correct
            UpdateGrid(grid, ships, impactPoint[0], i);
        }
    }

    for (int i = impactPoint[0] - 1;
         i < impactPoint[0] + 2; i++) { // shooting a square on the impact point for the diagonals
        for (int j = impactPoint[1] - 1; j < impactPoint[1] + 2; j++) {
            if (i >= 0 && i < GRID_HEIGHT && j >= 0 && j < GRID_WIDTH) { // Verification to know if the cell number is correct
                UpdateGrid(grid, ships, i, j);
            }
        }
    }
    (inventory->qtyBomb)--;
}

void FireTactical(Grid *grid, Grid *ships, Boat boats[BOAT_NUMBER], int impactPoint[2], Inventory* inventory) {
    if (ships->board[impactPoint[0]][impactPoint[1]] != '_') {
        Boat boatHit = boats[IdentifyBoat(boats, impactPoint)];
        if (boatHit.orientation == 'H') {
            for (int i = boatHit.position[1]; i < boatHit.position[1] + boatHit.size; i++) {
                grid->board[impactPoint[0]][i] = 'X';
                ships->board[impactPoint[0]][i] = 'D';
            }
        } else {
            for (int i = boatHit.position[0]; i < boatHit.position[0] + boatHit.size; i++) {
                grid->board[i][impactPoint[1]] = 'X';
                ships->board[i][impactPoint[1]] = 'D';
            }
        }
    } else {
        grid->board[impactPoint[0]][impactPoint[1]] = 'O';
    }
    (inventory->qtyTactical)--;
}

void FireMissile(Boat *boats, char missilePicked, int *impactPoint, Inventory *inventory, Grid *grid, Grid *ships) {
    switch (missilePicked) { // Fires a type of missile according to what the user picked
        case 'S': // Simple missile
        case 's':
            FireSimple(grid, ships, impactPoint, inventory);
            break;
        case 'A': // Artillery missile
        case 'a':
            FireArtillery(grid, ships, impactPoint, inventory);
            break;
        case 'B': // Bomb missile
        case 'b':
            FireBomb(grid, ships, impactPoint, inventory);
            break;
        case 'T': // Tactical missile
        case 't':
            FireTactical(grid, ships, boats, impactPoint, inventory);
            break;
        default:
            printf("An error has occured.");
    }
}