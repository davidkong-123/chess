#include "memory"
#include "grid.h"
// getpiece

/*
class Grid;
class Chess;
class X;
*/

std::shared_ptr<Chess>& Grid::getpiece(X col, int row){
    return theGrid.at(row).at(static_cast<int>(col));
}