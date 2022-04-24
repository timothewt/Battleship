#ifndef PROJECT_MENU_H
#define PROJECT_MENU_H

// Prototypes :

int Menu(char* difficulty, char* gamemode, Grid* grid, Grid* ships, Inventory* inventory, Boat boats[BOAT_NUMBER]/*, emplacement du fichier à charger*/);
/* Asks the player if he wants to start a new game, load an existing one or leave the program
    @param difficulty : Difficulty of the game which will be set as easy (E), medium (M) or hard (H)
    @param gamemode : Game mode which will be set as classic (C), blind (B) or active (A)
    @param grid : Blank grid which will be filled from the data in the file
    @param ships : Grid of the ships 
    @param inventory : Empty inventory which will be filled from the data in the file
	@param boats[BOAT_NUMBER] : Array of all the boats of the game
    @param fichier à charger : Path of the file from which we set the other variables data
	@return 0 if the player makes a new game and 1 if he loads one
*/

void FillInventory(char difficulty, Inventory* inventory);
/* Fills the inventory with a number of missiles depending on the difficulty
    @param difficulty : Difficulty of the game (E,M,H)
    @param inventory : Inventory that we want to fill
*/

void SetInventory(Inventory *inventory, int simple, int artillery, int bomb, int tactical);
/* Set the quantity of each missile
    @param inventory : Inventory of the player with the number of missiles available
    @param simple : Qty of simple missile you want to set
    @param artillery : Qty of artillery missile you want to set
    @param bomb : Qty of bomb missile you want to set
    @param tactical : Qty of tactical missile you want to set
*/

#endif //PROJECT_MENU_H
