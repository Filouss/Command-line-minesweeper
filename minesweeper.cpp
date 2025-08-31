#include <vector>
#include "minesweeper.hpp"

#include <iostream>
#include <regex>

using namespace std;

int main(int argc, char* argv[]) {
    Minesweeper minesweeper;

    if (argc < 2 || argc > 4) {
        cout << "spatny pocet parametru programu, pro napovedu zadejte parametr --help.\n";
        return 1;
    }

    //check which configuration to create, if there is only one additional argument, create from preset
    if (argc == 2){minesweeper = Minesweeper(argv[1]);}

    //else the user has own dimensions and mine amount
    else {minesweeper = Minesweeper(stoi(argv[1]),stoi(argv[2]),stoi(argv[3]));}
    if(!minesweeper.getIsOver()) {
        minesweeper.startGame();
    }
    return 0;
}

void Minesweeper::startGame() {
    board.printBoard();
    while(!getIsOver()) {
        cout << "Hadejte lokace min tim, ze napisete x a y souradnice" << endl;
        //get the input from user
        getline(cin, playerInput);
        //validate the input
        if (!validInput()){continue;}
        //check if the player is flagging or placing a mine by checking if the first char is number
        if (playerInput[0] < '0' || playerInput[0] > '9') {
            flagCell(parseInput(playerInput));
        } else {
            doTurn(parseInput(playerInput));
        }
        getBoard().printBoard();

    }
    if (getPlayerWon()) {
        cout<<"Vyhra! :)"<<endl;
    } else {
        cout<<"Prohra! :("<<endl;
    }
    getBoard().printFinalBoard();
}

Minesweeper::Minesweeper( int height, int width, int minecount){
    isOver = false;
    if (minecount > width*height || minecount <= 0 || width < 1 || height < 1) {
        cout << "spatne hodnoty hry" << endl;
        isOver = true;
        return;
    }
    playerInput = "";
    // create board with set parameters
    Board b = Board(height,width,minecount);
    this->board = b;
}

void Minesweeper::doTurn(pair<int,int> chosenCoords) {
    //check if coords are in the grid
    if (chosenCoords.first == -1 && chosenCoords.second == -1) {
        cout << "souradnice mimo hranice hraciho pole!"<< endl;
        return;
    }
    // check if it's first turn
    if (firstTurn) {
        firstTurn = false;
        //if the cell is mine
        if (getCell(chosenCoords).getIsMine()) {
            //if it's mine switch with adjacent cell that doesn't have a mine
            Cell* guessed = &getCell(chosenCoords);
            Cell* toSwap = &board.findAdjNonMine(guessed->getLocation());
            guessed->setIsMine(false);
            toSwap->setIsMine(true);
            //find mines for adjacent cells after swapping
            for (Cell* neighbor : guessed->getAdjacentCells()) {
                neighbor->findAdjMines();
            }
            for (Cell* neighbor : toSwap->getAdjacentCells()) {
                neighbor->findAdjMines();
            }
        }
    }

    //if player chose a cell with mine, game is over
    if (getCell(chosenCoords).getIsMine()) {
        isOver = true;
        playerWon = false;
    }
    getCell(chosenCoords).setIsVisible(true);
    //check if this cell has 0 mines and uncover neighbours if so
    if (getCell(chosenCoords).getAdjMines()==0) {getCell(chosenCoords).uncoverMinelessNeighbours();}
    if (Board::uncoveredCellsAmount()==(Board::getHeight()*Board::getWidth()-Board::getMineAmount())) {
        isOver = true;
        playerWon = true;
    }
}

bool Minesweeper::getIsOver() {
    return isOver;
}

void Minesweeper::setIsOver(bool value) {
    isOver = value;
}

pair<int, int> Minesweeper::parseInput(string input) {
    string coord;
    pair<int, int> result = {-1, -1};
    //iterate through the string
    for (size_t i = 0; i < input.length(); i++) {
        //if the first char is not a number, skip to numbers
        if (input[i] != ' ' && (input[i] < '0' || input[i] > '9')) {i=2; }
        char c = input[i];
        if (c == ' ' || i == input.length() - 1) {
            //add the number to the second coord if it's the end of number or input
            if (result.first == -1) {
                result.first = stoi(coord);
                coord = "";
                continue;
            }
            //append the numbers
            coord += c;
            //add the rest to the first coord
            result.second = stoi(coord);
        } else {
            coord += c;
        }
    }
    //if the number is not in correct dimensions, return -1 -1 for later printing of a message
    if(!checkDimensions(result)) {
        return pair<int, int>(-1, -1);
    }
    return result;
}

void Minesweeper::flagCell(pair<int, int> cellCoords) {
    //if the coords are -1 -1 the input was out of the borders
    if (cellCoords.first == -1 && cellCoords.second == -1) {
        cout << "souradnice mimo hranice hraciho pole!"<< endl;
        return;
    }
    //flag the cell
    bool oldValue = getCell(cellCoords).getFlagged();
    getCell(cellCoords).setFlagged(!oldValue);
}

Cell& Minesweeper::getCell(pair<int, int>& cellCoords) {
    return Board::getMap()[cellCoords.second][cellCoords.first];
}


Board &Minesweeper::getBoard() {
    return this->board;
}

bool Minesweeper::getPlayerWon() {
    return this->playerWon;
}

bool Minesweeper::validInput() {
    //regex for checking if the input was two numbers or f and two numbers
    regex uncoverPattern("^\\d+\\s+\\d+$");
    regex flagPattern("^f\\s+\\d+\\s+\\d+$");

    if (regex_match(playerInput, uncoverPattern) || regex_match(playerInput, flagPattern)) {
        return true;
    }
    cout << "nevalidni input" << endl;
    return false;
}

bool Minesweeper::checkDimensions(pair<int, int> cellCoords) {
    if (cellCoords.second>=0 && cellCoords.second < Board::getWidth() && cellCoords.first>=0 && cellCoords.first<Board::getHeight()) {
        return true;
    }
    return false;
}

Minesweeper::Minesweeper(string preset) {
    isOver = false;
    playerInput = "";
    //create board with the correct preset
    if (preset=="beg") {
        Board b = Board(9,9,9);
        this->board = b;
    } else if (preset=="int") {
        Board b = Board(16,16,40);
        this->board = b;
    } else if (preset=="exp") {
        Board b = Board(16,30,99);
        this->board = b;
    //print the help guide
    } else if (preset=="--help") {
        printHelp();
        isOver = true;
    // no correct preset was received
    } else {
        cout << "spatny preset" << endl;
        isOver = true;
    }
}

Minesweeper::Minesweeper() {
}

void Minesweeper::printHelp() {
    string help = "Semestralni projekt na tema Minesweeper \n"
                  "Cilem hry je najit odhalit vsechna neminova pole mapy \n"
                  "Program se spousti dvema zpusoby:\n"
                  "1. Pomoci preddefinovanych scenaru beg(mapa 9x9 a 10 min), int(16x30 a 40 min) a exp(30x16 a 99 min) \n"
                  "     1.1 v tomto pripade se program spusti napr. pro beg scenar nasledovne: semestralka.exe beg \n"
                  "2. V libovolnem modu ktery je formatovan nasledovne: semestralka.exe [vyska] [sirka] [pocet min]\n"
                  "V prubehu hry uzivatel vybere dane pole pomoci zadani x a y souradnice, bod 0 0 je na hracim poli vlevo dole\n"
                  "Uzivatel take muze \"flaggovat\" policka a tim si dane pole oznaci \n"
                  "jako potencialni minu tim ze pred souradnice zada pismeno f";
    cout << help << endl;
}

