#ifndef PROJECT_SAVE_H
#define PROJECT_SAVE_H

// Prototypes :

void Save(char gamemode, Grid grid, Grid ships, Inventory inventory, Boat boats[BOAT_NUMBER]);
/* Saves the game in a text file where the grid, the game mode and inventory are saved
    @param gamemode : Game mode (C,B,A)
    @param grid : Grid of the game with (_,O,X)
    @param ships : Grid of the ships (_,B,D)
	@param boats[5] : Array of all the boats of the game
    @param inventory : Inventory where the missiles are stored
*/

int Load(char* gamemode, Grid* grid, Grid* ships, Inventory* inventory, Boat boats[BOAT_NUMBER]);
/* Loads a game from an external file
    @param gamemode : Game mode of the game which will be set in the function from the data in the file
    @param grid : Blank grid which will be filled from the data in the file
    @param ships : Grid of the ships 
    @param inventory : Empty inventory which will be filled from the data in the file
	@param boats[5] : Array of all the boats of the game
	@return 0 if the file doesn't exist and 1 if the game has been loaded
*/

#endif //PROJECT_SAVE_H