#ifndef PROJECT_MISSILES_H
#define PROJECT_MISSILES_H

// Prototypes :

int PickMissile(Inventory* inventory, char missileType);
/* Checks if the missile is available in the inventory, if so remove on from in
    @param inventory : Inventory of the player where the missiles are stored
    @param missileType : Type of the missile to check (S,A,B,T)
    @return 1 if the missile is available or 0 if it isn't
*/

int CheckQty(int* missileQty);
/* Checks if there is at least one missile of a type.
    @param missileQty : Quantity of the missile we want to know of
    @return 1 if there is one or more missile or 0 when there are no missile left
*/

void FireSimple(Grid* grid, Grid* ships, int impactPoint[2], Inventory* inventory);
/* Fires a simple missile where only the aimed box is affected
    @param grid : Grid of the game where the _ are replaced with O if nothing has been it or X if a boat has been hit
    @param ships : Grid of the ships where the B are replaced with D if a boat had been hit
    @param impactPoint[2] : Where the missile is aimed, {line,column}
    @param inventory : Inventory of the player where the missiles are stored
*/

void FireArtillery(Grid* grid, Grid* ships, int impactPoint[2], Inventory* inventory);
/* Fires a artillery missile, the whole line and column of the impact point is hit
    @param grid : Grid of the game where the _ are replaced with O if nothing has been it or X if a boat has been hit
    @param ships : Grid of the ships where the B are replaced with D if a boat had been hit
    @param impactPoint[2] : Where the missile is aimed, {line,column}
    @param inventory : Inventory of the player where the missiles are stored
*/

void FireBomb(Grid* grid, Grid* ships, int impactPoint[2], Inventory* inventory);
/* Fires a bomb, all the cells in a radius of 2 are hit (1 in diagonal)
    @param grid : Grid of the game where the _ are replaced with O if nothing has been it or X if a boat has been hit
    @param ships : Grid of the ships where the B are replaced with D if a boat had been hit
    @param impactPoint[2] : Where the missile is aimed, {line,column}
    @param inventory : Inventory of the player where the missiles are stored
*/

void FireTactical(Grid* grid, Grid* ships, Boat boats[BOAT_NUMBER], int impactPoint[2], Inventory* inventory);
/* Fires a tactical missile, only aims for one box but if a ship has been hit the whole ship is destroyed
    @param grid : Grid of the game where the _ are replaced with O if nothing has been it or X if a boat has been hit
    @param ships : Grid of the ships where the B are replaced with D if a boat had been hit
    @param boats[5] : Array of all the boats with their positions and sizes
    @param impactPoint[2] : Where the missile is aimed, {line,column}
    @param inventory : Inventory of the player where the missiles are stored
*/

void FireMissile(Boat *boats, char missilePicked, int *impactPoint, Inventory *inventory, Grid *grid, Grid *ships); 
/* Fires a missile according to what the user picked
    @param boats : Array of all the boats with their positions and sizes
    @param missilePicked : Type of missile the user picked
    @param impactPoint[2] : Where the missile is aimed, {line,column}
    @param inventory : Inventory of the player where the missiles are stored
    @param grid : Grid of the game where the _ are replaced with O if nothing has been it or X if a boat has been hit
    @param ships : Grid of the ships where the B are replaced with D if a boat had been hit
*/

#endif //PROJECT_MISSILES_H
