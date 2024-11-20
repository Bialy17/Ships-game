#include "board.h"
#include <iostream>

using namespace std;

Board::Board()
{
    remainingShips = 20;
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = '-';
            hiddenBoard[i][j] = '-';
        }
    }
}

Board::~Board() {}

void Board::showBoard() const {
    cout << "  ";
    for(int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;
    for(int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
        for(int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void Board::showHiddenBoard() const {
    cout << "  ";
    for(int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
    }
    cout << endl;
    for(int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";
        for(int j = 0; j < BOARD_SIZE; j++) {
            cout << hiddenBoard[i][j] << " ";
        }
        cout << endl;
    }
}

void Board::clearScreen() const
{
    cout << "\033[2J\033[1;1H";
}

bool Board::shoot(int row, int col)
{
    if (hiddenBoard[row][col] != '-')
    {
        return false;
    }

    if (board[row][col] == 'x')
    {
        hiddenBoard[row][col] = 'X';
        board[row][col] = 'X';
        remainingShips--;
        return true;
    }
    else
    {
        hiddenBoard[row][col] = 'O';
        board[row][col] = 'O';
    }
    return false;
}

bool Board::isGameOver() const
{
    return remainingShips == 0;
}

int Board::getBoardSize()
{
    return BOARD_SIZE;
}

bool Board::isCellEmpty(int row, int col) const {
        return board[row][col] == '-';
}

void Board::placeShip(int row, int col) {
    board[row][col] = 'x';
}

void Board::occupyCell(int row, int col) {
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(board[i][j] == '-' && 
               (i > 0 && board[i-1][j] == 'x' || 
                i < 9 && board[i+1][j] == 'x' || 
                j > 0 && board[i][j-1] == 'x' || 
                j < 9 && board[i][j+1] == 'x' || 
                i > 0 && j < 9 && board[i-1][j+1] == 'x' || 
                i < 9 && j < 9 && board[i+1][j+1] == 'x' || 
                i > 0 && j > 0 && board[i-1][j-1] == 'x' || 
                i < 9 && j > 0 && board[i+1][j-1] == 'x'))
            {
                board[i][j] = '~';
            }
        }
    }
}

void Board::cancelOccupiedCells(int row, int col)
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(board[i][j] == '~')
            {
                board[i][j] = '-';
            }
        }
    }
}

bool Board::canPlaceHorizontally(int firstRow, int firstCol, int length)
{
    if (firstCol + length <= BOARD_SIZE) {
        bool canPlaceRight = true;
        for (int i = 0; i < length; i++) {
            if (board[firstRow][firstCol + i] != '-') {
                canPlaceRight = false;
                break;
            }
        }
        if (canPlaceRight) {
            return true;
        }
    }

    if (firstCol - length + 1 >= 0) {
        bool canPlaceLeft = true;
        for (int i = 0; i < length; i++) {
            if (board[firstRow][firstCol - i] != '-') {
                canPlaceLeft = false;
                break;
            }
        }
        if (canPlaceLeft) {
            return true;
        }
    }
    return false;
}

bool Board::canPlaceVertically(int firstRow, int firstCol, int length)
{
    if (firstRow + length <= BOARD_SIZE) {
        bool canPlaceUp = true;
        for (int i = 0; i < length; i++) {
            if (board[firstRow + i][firstCol] != '-') {
                canPlaceUp = false;
                break;
            }
        }
        if (canPlaceUp) {
            return true;
        }
    }

    if (firstRow - length + 1 >= 0) {
        bool canPlaceDown = true;
        for (int i = 0; i < length; i++) {
            if (board[firstRow - i][firstCol] != '-') {
                canPlaceDown = false;
                break;
            }
        }
        if (canPlaceDown) {
            return true;
        }
    }
    return false;
}

void Board::resetBoard()
{
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = '-';
        }
    }
}

bool Board::isCellShot(int row, int col)
{
    if(hiddenBoard[row][col] == 'X' || hiddenBoard[row][col] == 'O')
    {
        return false;
    }
    else{
        return true;
    }
}
