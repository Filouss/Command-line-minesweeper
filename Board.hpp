#ifndef BOARD_HPP
#define BOARD_HPP
#include <vector>

#include "Cell.hpp"

using namespace std;

/**
 * @class Board
 * @brief A class representing the board of minesweeper.
 *
 * Contains the logic of creating the gameboard
 */
class Board {
    static int height;
    static int width;
    ///amount of mines to spawn in the board
    static int mineAmount;
    /// ratio of mine cells to non-mine cells
    float mineRatio;
    static std::vector<std::vector<Cell>> map;

    /**
     * @brief this method creates the 2D grid of cells
     */
    void createMap();
    /**
     *@brief this method sets up cell variables which are able to
     *be determined only after creating up the map
     */
    void setupCells();
public:
    Board();
    Board(int height, int width, int mineAmount);
    /**
     * @brief prints out the board to terminal
     */
    void printBoard();
    /**
     * @brief returns 2D map containing the cells
     */
    static std::vector<std::vector<Cell>>& getMap();
    static int getHeight();
    static int getWidth();
     /**
     * @brief retursn amounnt of uncovered cells to check if the user has uncovered all non-mine cells
     */
    static int uncoveredCellsAmount();
    static int getMineAmount();
     /**
     * @brief returns adjacent mine that is not mine
     */
    Cell& findAdjNonMine(pair<int, int> &cellCoords);
    /**
     * @brief prints out the board with all cells uncovered
     */
    void printFinalBoard();
};

#endif
