#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "verifications.h"

int IsAlive(Boat boat, Grid ships) {
    if (boat.orientation == 'H') {
        for (int i = boat.position[1]; i < boat.position[1] + boat.size; i++) {
            if (ships.board[boat.position[0]][i] == 'B') return 1;
        }
    } else {
        for (int i = boat.position[0]; i < boat.position[0] + boat.size; i++) {
            if (ships.board[i][boat.position[1]] == 'B') return 1;
        }
    }

    return 0;
}

int CheckInventory(Inventory inventory) {
    if (inventory.qtyBomb == 0 &&
        inventory.qtySimple == 0 &&
        inventory.qtyArtillery == 0 &&
        inventory.qtyTactical == 0) {
        return 1;
    } else {
        return 0;
    }
}

void ClearConsole() {
#ifdef WIN32 // If the OS is Windows
    system("cls");
#elif __linux__ // If the OS is Linux
    system ("clear");
#elif __APPLE__ // If the OS is MacOS
	printf('\33c\e[3J');
#else
    printf("Error, not defined in this platform");
#endif
}