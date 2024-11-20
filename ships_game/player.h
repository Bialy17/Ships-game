#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include <string>
#include "ship.h"
#include <vector>

using namespace std;

class Player {
private:
    Board board;
    Board hiddenBoard;
    string playerName;
    int playerWins = 0;
    vector<Ship> ships;
public:
    Player();
    ~Player();

    void placeShipElements(int &row, int &col, int i, Ship& ship);
    void createShips();
    void placeFirstElement(int &row, int &col, int &firstRow, int &firstCol, int &direction, bool &validInput, int &length, Ship &ship);
    void isShipInStraightLine(int &row, int &col, int &firstRow, int &firstCol, int &direction, bool &validInput);
    void isShipPlacedHorizontally(int &row, int &col, int &i, int &firstRow, int &firstCol, int &direction, bool &validInput);
    void isShipPlacedVertically(int &row, int &col, int &i, int &firstRow, int &firstCol, int &direction, bool &validInput);
    void canShipBePlaced(int &row, int &col, int &i, int &firstRow, int &firstCol, int &direction, bool &validInput, int &length, Ship &ship);
    void setShips();
    Board& getBoard();
    Board& getHiddenBoard();
    void setPlayerName(); 
    string getPlayerName();
    int getPlayerWins();
    void addPlayerWin();
};

#endif
