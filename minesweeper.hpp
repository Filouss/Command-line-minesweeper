#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include <string>

#include "Board.hpp"
using namespace std;

/**
 * @class Minesweeper
 * @brief A class representing the game.
 *
 * Contains the logic of the game loop
 */
class Minesweeper {
    Board board;
    ///indicates if the game is finished
    bool isOver;
    ///indicates if player won by uncovering all mines
    bool playerWon;
    ///indicates if the turn is first
    bool firstTurn = true;
public:
    string playerInput;
    Minesweeper();
    ///constructor from preset
    Minesweeper(string preset);
    ///constructor for sandbox values
    Minesweeper(int height, int width, int minecount);
    /// this method starts the game loop
    void startGame();
    bool getIsOver();
    void setIsOver(bool value);
    ///this method performs a turn on the coordinates the player has chosen
    void doTurn(pair<int,int> chosenCoords);
    ///this method parses the input into pair of coordinates
    pair<int, int> parseInput(string input);
    ///this method flags a cell on given coordinates
    void flagCell(pair<int,int> cellCoords);
    Cell& getCell(pair<int, int> &cellCoords);
    Board& getBoard();
    bool getPlayerWon();
    bool validInput();
    ///this method checks if said coordinates are in the borders of the map
    bool checkDimensions(pair<int,int> cellCoords);
    ///prints the usage guide
    void printHelp();
};
#endif
