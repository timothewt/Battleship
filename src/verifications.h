#ifndef PROJECT_VERIFICATIONS_H
#define PROJECT_VERIFICATIONS_H

// Prototypes :

int IsAlive(Boat boat, Grid ships);
/* Checks if a boat is alive, ie if there is still at least one 'B' on the boat
    @param boat : Boat to check
    @param ships : Grid of the ships
    @return 1 if the boat is alive and 0 if it isn't
*/

int CheckInventory(Inventory inventory); 
/* Checks if the inventory is empty, ie all the missiles quantity are at 0
    @param inventory : Inventory of the player
    @return 0 if the inventory isn't empty and 1 if the inventory is empty
*/

void ClearConsole();
// Checks the OS and clear the console with the command of the OS

#endif //PROJECT_VERIFICATIONS_H
