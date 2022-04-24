#ifndef PROJECT_GRID_H
#define PROJECT_GRID_H

void FillGrid(Grid* grid);
/* Fills the whole grid with '_'
    @param *grid : Grid to be filled with '_'
*/

void ShowGrid(Grid grid);
/* Displays the grid on the console
    @param grid : Grid to display
*/

void PlaceBoatsRandomly(Boat boats[BOAT_NUMBER], Grid* ships);
/* Randomly places all the boats on the grid
    @param boats[5] : Array of Boat structures that only contains the size of the boats, to be filled with position and orientation
    @param ships : Empty grid of all the ships, to be filled with boats as 'B'
*/

void PlaceBoat(Boat boat, Grid* ships);
/* Places a boat on the grid (fill is position with B's)
    @param boat : Boat that is going to be placed
    @param ships : Grid of all the ships where the boat is placed
*/

void PlaceAllBoats(Boat boats[BOAT_NUMBER], Grid* ships);
/* Fills the grid with _ and places all the boats from the array on the ships grid
    @param boats[5] : Array of all the boats with the positions sizes and orientations
    @param ships : Grid of the ships where the boats are placed
*/

int MoveBoat(Boat* boat, Grid* ships, Boat boats[5], int isAlive);
/* Moves a boat from 1 to 3 cells if possible, if it's not the boat isn't moved.
    @param boat : Boat that is going to MoveBoat
    @param ships : Grid of ships that is going to be modified when the boat moves
    @return 1 if the boat has moved or 0 if it hasn't
*/	

int IdentifyBoat(Boat boat[BOAT_NUMBER], int coordinates[2]);
/* Gives the number of the boat targetted
    @param boat : Array of all the boats on the grid
    @param coordinates[2] : Coordinates of the targetted cell {line,column}
    @return the number of the boat targetted in the boat array
*/

int CountBoatCells(Grid ships);
/* Counts the remaining cells with a non-destroyed boat (cells with B)
    @param ships : Grid with all the ships
    @return the number of cells with a 'B'
*/

int CountBoats(Boat boats[BOAT_NUMBER]);
/* Counts the number of boats which are still alive
    @param boats[5] : Array of all the boats of the game
    @return the number of boats that are still alive.
*/

void UpdateBoatCells(Boat* boats, Grid ships);
/* Changes the cells of the boat structures with the destroyed parts.
    @param boats : Boats to update
    @param ships : Grid of all the ships
*/

void UpdateGrid(Grid *grid, Grid *ships, int a, int b);
/* Changes the grid values where a missile was shot, put X if a boat is touched and O if not
    @param grid : Grid of the game
    @param ships : Grid of the ships
    @param a : line of the cell updated
    @param b : column of the cell updated
*/

#endif //PROJECT_GRID_H