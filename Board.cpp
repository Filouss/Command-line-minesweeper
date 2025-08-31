#include "Board.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <set>

#include "Cell.hpp"

using namespace std;

int Board::height = 0;
int Board::width = 0;
int Board::mineAmount=0;
std::vector<std::vector<Cell>> Board::map;

Board::Board(int width, int height, int mineCount) {
    Board::height = height;
    Board::width = width;
    Board::mineAmount = mineCount;
    mineRatio = (height*width)/mineAmount;
    map = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
    createMap();
    setupCells();
}


void Board::createMap() {
    pair <int,int> coord;
    int remainingMines = mineAmount ;
    int remainingCellCount = height*width;
    //create a random generator
    std::mt19937 gen(std::random_device{}());
    //iterate through each element of the 2d grid
    for (int i = height -1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            //create the coords and the ratio at which the chance for the cell to be mine will be determined
            coord = make_pair(j,i);
            double mineRatio = (double) remainingMines/remainingCellCount;
            std::uniform_real_distribution<double> dist(0.0, 1.0);
            bool isMine = dist(gen) < mineRatio;
            //if all mines are set, the rest will not be mines
            if (remainingMines == 0) {
                map[i][j] = Cell(coord,false);
            }else {
                map[i][j] = Cell(coord,isMine);
                if (isMine){remainingMines--;}
            }
            remainingCellCount--;

        }
    }

}

void Board::printBoard() {
    string rowDivider = string(4*width, '-');
    string mineGraphic = " ";
    // print with visible mines for testing
    for (int i = height-1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            cout << j << "-" << map[i][j].getIsMine() << '/' << map[i][j].getAdjMines() <<  "-" << i << "  ";
        }
        cout << endl;
    }
    cout << endl << rowDivider << '-' << endl;
    for (int i = height-1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            //get the number of adjacent mines to print if cell is visible
            if (map[i][j].getIsVisible()) {
                mineGraphic = to_string(map[i][j].getAdjMines());
            // if the cell is flagged, print "P"
            } else if (map[i][j].getFlagged()){
                mineGraphic = "P";
            }
            cout << '|' << " " << mineGraphic << " ";
            mineGraphic = " ";
        }
        cout << '|' << endl << rowDivider << '-' << endl;
    }
}

void Board::setupCells() {
    //for each cell create array of neighbouring cells and get the number of adjacent mines
    for (int i = height -1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            map[i][j].getAdjacentCells();
            map[i][j].findAdjMines();
        }
    }
}


int Board::getHeight() {
    return height;
}

int Board::getWidth() {
    return width;
}

std::vector<std::vector<Cell>>& Board::getMap() {
    return map;
}

int Board::uncoveredCellsAmount() {
    int counter = 0;
    //count the amount of visible cells
    for (int i = height -1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            if (map[i][j].getIsVisible()) {
                counter++;
            }
        }
    }
    return counter;
}

int Board::getMineAmount() {
    return mineAmount;
}

Board::Board() {

}

Cell &Board::findAdjNonMine(pair<int, int> &cellCoords) {
    static set<pair<int, int>> visited;
    // if this cell was not visited and is not a mine, return it
    if (!visited.count(cellCoords)) {
        visited.insert(cellCoords);
        for (auto cell : map[cellCoords.second][cellCoords.first].getAdjacentCells()) {
            if (!cell->getIsMine()) {
                visited.clear();
                return *cell;
            }
        }

        for (auto cell : map[cellCoords.second][cellCoords.first].getAdjacentCells()) {
                return findAdjNonMine(cell->getLocation());
        }
    }
}


void Board::printFinalBoard() {
    string rowDivider = string(4*width, '-');
    string mineGraphic = " ";
    cout << endl << rowDivider << '-' << endl;
    for (int i = height-1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            //get the number of adjacent mines to print if cell is visible
            if (!map[i][j].getIsMine()) {
                mineGraphic = to_string(map[i][j].getAdjMines());
                // if the cell is flagged, print "P"
            } else {
                mineGraphic = "*";
            }
            cout << '|' << " " << mineGraphic << " ";
            mineGraphic = " ";
        }
        cout << '|' << endl << rowDivider << '-' << endl;
    }
}
