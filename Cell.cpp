#include "Cell.hpp"

#include <iostream>
#include <vector>
#include <utility>
#include "Board.hpp"

using namespace std;

Cell::Cell(pair<int,int> coords,bool isMine) {
    this->location = coords;
    this->isVisible = false;
    this->isMine = isMine;
    this->flagged = false;
}

Cell::Cell() {
}

bool Cell::getIsMine() {
    return this->isMine;
}

int Cell::getAdjMines() {
    return this->adjMineCells;
}

void Cell::findAdjMines() {
    this->adjMineCells = 0;
    //iterate through each adjacent cell
    for (const auto cell: adjacentCells) {
        if (cell->getIsMine()) {
            //inc adjminecells if found
            this->adjMineCells++;
        }
    }
}

bool Cell::getFlagged() {
    return flagged;
}

void Cell::setFlagged(bool flagged) {
    this->flagged = flagged;
}

void Cell::setIsVisible(bool isVisible) {
    this->isVisible = isVisible;
}

bool Cell::getIsVisible() {
    return this->isVisible;
}

std::pair<int, int> &Cell::getLocation() {
    return this->location;
}


void Cell::uncoverMinelessNeighbours() {
    //iterate through each adjacent cell
    for (const auto cell : adjacentCells) {
        //if not mine, not visible, make it visible and if no adjacen cells are mine, call this method on the cell
        if (!cell->getIsMine() && !cell->getIsVisible()) {
            cell->setIsVisible(true);
            if (cell->adjMineCells == 0 ){cell->uncoverMinelessNeighbours();}
        }
    }
}

std::vector<Cell *> Cell::getAdjacentCells() {
    vector<Cell *> adjacentCells;
    //get all adjacent coordinates
    vector<pair <int,int> > adjacent ={{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,1},{1,-1},{-1,-1}};
    for (const pair <int,int> coord : adjacent) {
        pair<int,int> newCoord = make_pair(coord.first+location.first ,coord.second+location.second);
        //check if the coordinates are in the dimensions of the board
        if (newCoord.second>=0 && newCoord.second < Board::getHeight() && newCoord.first>=0 && newCoord.first<Board::getWidth()) {
            //add the cell to the list
            Cell* cellPtr = &Board::getMap()[newCoord.second][newCoord.first];
            adjacentCells.push_back(cellPtr);
        }
    }
    this-> adjacentCells=adjacentCells;
    return adjacentCells;
}


void Cell::setIsMine(bool isMine) {
    this->isMine = isMine;
}

