#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "structures.h"
#include "menu.h"
#include "save.h"

int Menu(char *difficulty, char *gamemode, Grid *grid, Grid *ships, Inventory *inventory, Boat boats[BOAT_NUMBER]) {
    char option;
    do {
        printf("Welcome to Battlehip !\nType :\n- 'N' if you want to start a new game\n- 'L' if you want to load a previous game\n- 'Q' if you want to quit\n");
        scanf(" %c", &option);
        switch (option) {
            case 'N':
            case 'n':
                do {
                    printf("You decided to start a new game. You now have to choose a gamemode. Type :\n- 'C' for classic\n- 'B' for blind (the grid doesn't appear after your turn)\n- 'A' for active (boats can move)\n");
                    scanf(" %c", &*gamemode);
                } while (*gamemode != 'C' && *gamemode != 'c' &&
                         *gamemode != 'B' && *gamemode != 'b' &&
                         *gamemode != 'A' && *gamemode != 'a');

                do {
                    printf("You now have to choose a difficulty. Type :\n- 'E' for easy (5 artillery, 6 bombs, 5 tactical, 15 simple)\n- 'M' for medium (3 artillery, 4 bombs, 4 tactical, 10 simple)\n- 'H' for hard  (1 artillery, 2 bombs, 3 tactical, 15 simple)\n");
                    scanf(" %c", &*difficulty);
                } while (*difficulty != 'E' && *difficulty != 'e' &&
                         *difficulty != 'M' && *difficulty != 'm' &&
                         *difficulty != 'H' && *difficulty != 'h');

                return 0;
                break;
            case 'L':
            case 'l':
                if (!Load(gamemode, grid, ships, inventory, boats)) {
                    option = 'Z'; // if load returns 0, changes option value to Z so the while loops once again
                } else {
                    printf("\nThe game has been loaded correctly\n");
                    return 1;
                }
                break;
            case 'Q':
            case 'q':
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Please type a correct option.\n");
        }
    } while (option != 'N' && option != 'n' &&
             option != 'L' && option != 'l' &&
             option != 'Q' && option != 'q');
    return 0;
}

void SetInventory(Inventory *inventory, int simple, int artillery, int bomb, int tactical) {
    inventory->qtySimple = simple;
    inventory->qtyArtillery = artillery;
    inventory->qtyBomb = bomb;
    inventory->qtyTactical = tactical;
}

void FillInventory(char difficulty, Inventory *inventory) {
    if (difficulty == 'E' || difficulty == 'e') { // Easy difficulty
        SetInventory(inventory, 15, 5, 6, 5);
    } else if (difficulty == 'M' || difficulty == 'm') { // Medium difficulty
        SetInventory(inventory, 10, 3, 4, 4);
    } else { // Hard difficulty         
        SetInventory(inventory, 15, 1, 2, 3);
    }
}
