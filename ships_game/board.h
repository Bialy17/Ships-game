#ifndef BOARD_H
#define BOARD_H
#include <iostream>
//#include <vector>
//#include "ship.h"

class Board
{
private:
    static const int BOARD_SIZE = 10;
    char board[BOARD_SIZE][BOARD_SIZE];
    char hiddenBoard[BOARD_SIZE][BOARD_SIZE];
    //vector<Ship> ships;
    int remainingShips;

public:
    Board();
    ~Board();

    void showBoard() const;
    void showHiddenBoard() const;
    //void setShips();
    //bool isValidShipPlacement(int firstRow, int firstCol, int row, int col, int direction, int index);
    bool shoot(int row, int col);
    bool isGameOver() const;
    static int getBoardSize();
    bool isCellEmpty(int row, int col) const;
    void placeShip(int row, int col);
    void occupyCell(int row, int col);
    void cancelOccupiedCells(int row, int col);
    bool canPlaceHorizontally(int firstRow, int firstCol, int length);
    bool canPlaceVertically(int firstRow, int firstCol, int length);
    void resetBoard();
};
#endif