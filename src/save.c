#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "save.h"
#include "grid.h"

void Save(char gamemode, Grid grid, Grid ships, Inventory inventory, Boat boats[BOAT_NUMBER]) {
    FILE *saveFile = fopen("saveGame.txt", "w"); // Open the saveGame.txt file, or create the file if it doesn't exist, replace the content of the file if it exists

    if (fprintf(saveFile, "gamemode=%c\n", gamemode) < 0 ||
        (fprintf(saveFile, "inventory : qtySimple=%d, qtyBomb=%d, qtyTactical=%d, qtyArtillery=%d\n",
                 inventory.qtySimple, inventory.qtyBomb, inventory.qtyTactical, inventory.qtyArtillery) < 0)) { // If there is an error when writing in the saveGame.txt file
        printf("Error, game has not been saved.\n");
        if (!remove("saveGame.txt")) { // Delete the saveGame.txt file (if there was an error)
            printf("The saveGame file has been deleted.\n");
        }
    }

    if ((fprintf(saveFile, "\n") < 0) ||
        (fprintf(saveFile, "position[line] | position[column] | size | orientation | alive\n") < 0)) {
        printf("Error, game has not been saved.\n");
        if (!remove("saveGame.txt")) {
            printf("The saveGame file has been deleted.\n");
        }
    }
    for (int i = 0; i < BOAT_NUMBER; i++) {
        if ((fprintf(saveFile, "boat %d : %d, %d, %d, %c, %d\n", i, boats[i].position[0], boats[i].position[1],
                     boats[i].size, boats[i].orientation, boats[i].alive) < 0)) {
            printf("Error, game has not been saved.\n");
            if (!remove("saveGame.txt")) {
                printf("The saveGame file has been deleted.\n");
            }
        }

        for (int j = 0; j < boats[i].size; j++) {
            if ((fprintf(saveFile, "%c\n", boats[i].cells[j]) < 0)) {
                printf("Error, game has not been saved.\n");
                if (!remove("saveGame.txt")) {
                    printf("The saveGame file has been deleted.\n");
                }
            }
        }
    }

    if ((fprintf(saveFile, "\n") < 0)) {
        printf("Error, game has not been saved.\n");
        if (!remove("saveGame.txt")) {
            printf("The saveGame file has been deleted.\n");
        }
    }

    for (int i = 0; i < grid.height; i++) { // Goes through all the grid 
        for (int j = 0; j < grid.width; j++) {
            if ((fprintf(saveFile, "coordinate : (%d;%d) = %c\n", i, j, grid.board[i][j]) < 0)) {
                printf("Error, game has not been saved.\n");
                if (!remove("saveGame.txt")) {
                    printf("The saveGame file has been deleted.\n");
                }
            }
        }
    }
    fclose(saveFile);
}


int Load(char *gamemode, Grid *grid, Grid *ships, Inventory *inventory, Boat boats[BOAT_NUMBER]) {

    FILE *saveFile = fopen("saveGame.txt", "r"); // Open the saveGame.txt file to read the content
    if (saveFile == NULL) { // if the saveGame.txt file doesn't exist
        printf("No game to load\n");
        return 0; // Ask the user to create another game or quit again
    } else {
        fscanf(saveFile,
               "gamemode = %c\ninventory : qtySimple=%d, qtyBomb=%d, qtyTactical=%d, qtyArtillery=%d\nposition[line] | position[column] | size | orientation | alive\n",
               gamemode, &inventory->qtySimple, &inventory->qtyBomb, &inventory->qtyTactical, &inventory->qtyArtillery);

        for (int k = 0; k < BOAT_NUMBER; k++) {
            fscanf(saveFile, "boat %d : %d, %d, %d, %c, %d\n", &k, &boats[k].position[0], &boats[k].position[1],
                   &boats[k].size, &boats[k].orientation, &boats[k].alive);
            for (int l = 0; l < boats[k].size; l++) {
                fscanf(saveFile, "%c\n", &boats[k].cells[l]);
            }
        }

        for (int i = 0; i < grid->height; i++) {
            for (int j = 0; j < grid->width; j++) {
                fscanf(saveFile, "coordinate : (%d;%d) = %c\n", &i, &j, &grid->board[i][j]);
            }
        }
    }
    fclose(saveFile);
    PlaceAllBoats(boats, ships); // Places boats
    return 1; //game has been loaded: continue
}
