#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "structures.h"
#include "grid.h"
#include "menu.h"
#include "missiles.h"
#include "save.h"
#include "verifications.h"

int main() {

    char gamemode;
    char difficulty;
    char playAgain; // 'N' : No ; 'Y' : Yes
    Inventory inventory;
    Grid grid; // Grid of the game that the player sees
    Grid ships; // Grid of the boats only for the program
    grid.height = ships.height = GRID_HEIGHT; // Setting grid height at GRID_HEIGHT 
    grid.width = ships.width = GRID_WIDTH; // Setting grid width at GRID_WIDTH
    Boat boats[BOAT_NUMBER];
    boats[0].size = 2; // Sizes of the boats
    boats[1].size = 3;
    boats[2].size = 3;
    boats[3].size = 4;
    boats[4].size = 5;

    srand(time(0));

    do { // Main game loop

        for (int i = 0; i < BOAT_NUMBER; i++) { // Changing all boats status to alive
            boats[i].alive = 1;
            boats[i].cells = malloc(boats[i].size * sizeof(char)); // Allocating the size of the cells array according to the size of the boat
            for (int j = 0; j < boats[i].size; j++) { // Filling all the cells with brand new boats
                boats[i].cells[j] = 'B';
            }
        }

        ClearConsole();

        if (!Menu(&difficulty, &gamemode, &grid, &ships, &inventory, boats)) {
            FillInventory(difficulty, &inventory); //Filling the inventory according to the difficulty
            FillGrid(&grid); // Filling the grids with underscores
            FillGrid(&ships);
            PlaceBoatsRandomly(boats, &ships); // Placing the boats on the field
        } else {
            PlaceAllBoats(boats, &ships);
        }

        ClearConsole(); //clear the console for more visibility
        printf("The grid is shown below :\n");
        ShowGrid(grid); // Displaying the grid

        do {
            char missilePicked;
            char keepPlaying;
            int impactPoint[2];

            printf("\n%d boats are alive and %d squares are remaining.\nInventory :\n- %d Simple missile(s)\n- %d Artillery missile(s)\n- %d Bomb missile(s)\n- %d Tactical missile(s)",
                   CountBoats(boats), CountBoatCells(ships), inventory.qtySimple, inventory.qtyArtillery,
                   inventory.qtyBomb, inventory.qtyTactical);

            do {
                printf("\nType 'K' to keep playing and 'S' to save and quit : ");
                scanf(" %c", &keepPlaying);
            } while (keepPlaying != 'K' && keepPlaying != 'k' && keepPlaying != 'S' && keepPlaying != 's');

            if (keepPlaying == 'S' || keepPlaying == 's') {
                Save(gamemode, grid, ships, inventory, boats);
                printf("\nThank you for playing our game !\n");
                sleep(2); // Pause to have time to see the message
                exit(EXIT_SUCCESS);
            }
            printf("\nWhich missile do you want to use ? Type 'S' for a simple, 'A' for artillery, 'B' for bomb and 'T' for tactical :\n");
            scanf(" %c", &missilePicked);
			if (!PickMissile(&inventory, missilePicked)) {
				printf("\nYou don't have anymore missile of this type.\n");
				missilePicked = 'Z';
			}

            while (missilePicked != 'S' && missilePicked != 's' &&
                   missilePicked != 'B' && missilePicked != 'b' &&
                   missilePicked != 'A' && missilePicked != 'a' &&
                   missilePicked != 'T' && missilePicked != 't') { // Check if the input is correct
                printf("Please pick a correct missile. Type 'S', 'A', 'B' or 'T' : ");
                scanf(" %c", &missilePicked);

				if (!PickMissile(&inventory, missilePicked)) {
					printf("You don't have anymore missile of this type.\n");
					missilePicked = 'Z';
				}
            }

            do { // Asks the user for the coordinates where he wants to shoot
                printf("Type the number of the line you want to shoot (1 to %d) : ", GRID_HEIGHT);
                scanf("%d", &impactPoint[0]);
            } while (impactPoint[0] > GRID_HEIGHT || impactPoint[0] < 1);
            do {
                printf("Type the number of the column you want to shoot (1 to %d) : ", GRID_WIDTH);
                scanf("%d", &impactPoint[1]);
            } while (impactPoint[1] > GRID_WIDTH || impactPoint[1] < 1);

            ClearConsole(); //clear the console for more visibility (the grid is always at the same place)

            impactPoint[0]--; // Decreasing coordinates by 1 because arrays start at 0
            impactPoint[1]--;

            FireMissile(boats, missilePicked, impactPoint, &inventory, &grid, &ships);

            for (int i = 0; i < BOAT_NUMBER; i++) { // Updates alive status for all the boats
                boats[i].alive = IsAlive(boats[i], ships);
            }

            if (gamemode != 'B' && gamemode != 'b') { // Doesn't show the grid if game mode is Blind
                printf("\n");
                ShowGrid(grid);
                printf("\n");
            } else {
				for (int i = 0; i < grid.height; i++) {
					for (int j = 0; j < grid.width; j++) {
						if (grid.board[i][j] == 'X') {
							printf("Boat touched : (%d; %d)\n", i+1, j+1); // Print the coordinates where a boat is touched
						}
					}
				}
				FillGrid(&grid); // Fill the grid with underscores to only print the coordinates where a boat is touched of each turn
			}

            for (int i = 0; i < BOAT_NUMBER; i++) { // Updating all the boats cells
                UpdateBoatCells(&boats[i], ships);
            }

            if (gamemode == 'A' || gamemode == 'a') {
                int randBoat = rand() % BOAT_NUMBER;
                if (MoveBoat(&boats[randBoat], &ships, boats, boats[randBoat].alive)) {
                    printf("A boat has moved.\n");
                } else {
                    printf("No boat moved.\n");
                }
            }

        } while (CountBoats(boats) > 0 && !CheckInventory(inventory));

        if (!CountBoats(boats)) {
            printf("\nCongratulations ! You won the game !\nThe grid below shows the destroyed ships :\n\n");
        } else {
            printf("You ran out of missiles. You lost the game.\nThe grid below shows the ships (the B parts are not destroyed while the D parts are) :\n\n");
        }

        ShowGrid(ships);

        printf("\nDo you want to play again ? (Y/N) :");
        scanf(" %c", &playAgain);
    } while (playAgain == 'Y' || playAgain == 'y');

    for (int i = 0; i < BOAT_NUMBER; i++) {
        free(boats[i].cells);
    }

    printf("\nThank you for playing our game !\n");
    sleep(2); // Pause to have time to see the message
    return 1;
}
