#ifndef POINT_HPP
#define POINT_HPP

#include <utility>
#include <vector>
/**
 * @class Cell
 * @brief A class representing an individual cell.
 */
class Cell {
    /// indicates whether the cell has mine
    bool isMine;
    /// list of neighbour cells
    std::vector<Cell*> adjacentCells;
    /// x and y coordinates of this cell in a pair
    std::pair<int, int> location;
    /// indicates whether the cell has been chosen by a user in a turn, if true the number of adjacent mine cells is visible during print out
    bool isVisible;
    /// number of adjacent cells with mines
    int adjMineCells = 0;
    /// indicates if the cell is flagged
    bool flagged;

public:
    Cell(std::pair<int,int> coords,bool isMine);
    Cell();

    /**
     * @brief counts amount of mines on adjacent cells
     */
    void findAdjMines();
    /**
     * @brief true if this cell is mine, false if not
     */
    bool getIsMine();
    /**
     * @brief returns the amount of mines adjacent to this cell
     */
    int getAdjMines();
    /**
     * @brief returns true if this cell is flagged, false if not
     */
    bool getFlagged();
    void setFlagged(bool flagged);
    void setIsVisible(bool isVisible);
    bool getIsVisible();
    void setIsMine(bool isMine);
    std::pair<int,int>& getLocation();
    /**
     * @brief if this cell has zero adjacent cells with mines, it uncovers them and checks if any of them also have 0 and recursively continues uncovering
     */
    void uncoverMinelessNeighbours();
    std::vector<Cell*> getAdjacentCells();
};

#endif
