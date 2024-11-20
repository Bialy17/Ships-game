#include "player.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <limits>

Player::Player()
{
}

Player::~Player()
{
}

void Player::placeShipElements(int &row, int &col, int i, Ship& ship)
{
    cout << "Set " << i + 1 << ". element's row of " << ship.getName() << "(0-9): ";
    while (!(cin >> row) || row < 0 || row >= board.getBoardSize()) {
        cout << "Invalid input! Please enter a valid number between 0 and 9." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Set " << i + 1 << ". element's row of " << ship.getName() << "(0-9): ";
    }
    cout << "Set " << i + 1 << ". element's column of " << ship.getName() << "(0-9): ";
    while (!(cin >> col) || col < 0 || col >= board.getBoardSize()) {
        cout << "Invalid input! Please enter a valid number between 0 and 9." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Set " << i + 1 << ". element's column of " << ship.getName() << "(0-9): ";
    }
}

void Player::createShips()
{
    ships.push_back(Ship(4, "4-masted ship"));

    for(int i = 0; i < 2; i++) {
        ships.push_back(Ship(3, "3-masted ship"));
    }
    for(int i = 0; i < 3; i++) {
        ships.push_back(Ship(2, "2-masted ship"));
    }
    for(int i = 0; i < 4; i++) {
        ships.push_back(Ship(1, "1-masted ship"));
    }
}

void Player::placeFirstElement(int &row, int &col, int &firstRow, int &firstCol, int &direction, bool &validInput, int &length, Ship& ship)
{
    firstRow = row;
    firstCol = col;
    bool canPlaceHorizontally = board.canPlaceHorizontally(firstRow, firstCol, length);
    bool canPlaceVertically = board.canPlaceVertically(firstRow, firstCol, length);
    if(canPlaceHorizontally || canPlaceVertically)
    {
        board.placeShip(row, col);
        validInput = true;
        if(canPlaceHorizontally && !canPlaceVertically)
        {
            direction = 0;
        }
        else if(!canPlaceHorizontally && canPlaceVertically)
        {
            direction = 1;
        }
        else{
            direction = -1;
        }
    }
    else{
        cout << "Error! No space to place the entire " << ship.getName() << " here." << endl;
        firstRow = firstCol = -1;
    }
}

void Player::isShipInStraightLine(int &row, int &col, int &firstRow, int &firstCol, int &direction, bool &validInput)
{
    if (row == firstRow && abs(col - firstCol) == 1)
    {
        direction = 0;
        board.placeShip(row, col);
        validInput = true;
    }
    else if (col == firstCol && abs(row - firstRow) == 1)
    {
        direction = 1;
        board.placeShip(row, col);
        validInput = true;
    }
    else
    {
        cout << "Error! Ship must be placed in a straight line." << endl;
    }
}

void Player::isShipPlacedHorizontally(int &row, int &col, int &i, int &firstRow, int &firstCol, int &direction, bool &validInput)
{
    if (row == firstRow && abs(col - firstCol) == i)
    {
        board.placeShip(row, col);
        validInput = true;
    }
    else if (row == firstRow && abs(col - firstCol) == 1)
    {
        board.placeShip(row, col);
        validInput = true;
        firstCol = col;
    }
    else
    {
        cout << "Error! Ship must be placed horizontally." << endl;
    }
}

void Player::isShipPlacedVertically(int &row, int &col, int &i, int &firstRow, int &firstCol, int &direction, bool &validInput)
{
    if (col == firstCol && abs(row - firstRow) == i)
    {
        board.placeShip(row, col);
        validInput = true;
    }
    else if (col == firstCol && abs(row - firstRow) == 1)
    {
        board.placeShip(row, col);
        validInput = true;
        firstRow = row;
    }
    else
    {
        cout << "Error! Ship must be placed vertically." << endl;
    }
}

void Player::canShipBePlaced(int &row, int &col, int &i, int &firstRow, int &firstCol, int &direction, bool &validInput, int &length, Ship &ship)
{
    if (row >= 0 && row < board.getBoardSize() && col >= 0 && col < board.getBoardSize())
    {
        if (board.isCellEmpty(row, col))
        {
            if (i == 0)
            {
                placeFirstElement(row, col, firstRow, firstCol, direction, validInput, length, ship);
            }
            else
            {
                if (direction == -1)
                {
                    isShipInStraightLine(row, col, firstRow, firstCol, direction, validInput);
                }
                else if (direction == 0)
                {
                    isShipPlacedHorizontally(row, col, i, firstRow, firstCol, direction, validInput);
                }
                else // direction == 1
                {
                    isShipPlacedVertically(row, col, i, firstRow, firstCol, direction, validInput);
                }
            }
        }
        else
        {
            cout << "Error! This cell is already occupied." << endl;
        }
    }
    else
    {
        cout << "Error! Element is off the board." << endl;
    }
}

void Player::setShips()
{
    int row, col;

    createShips();

    for (size_t shipIndex = 0; shipIndex < ships.size(); shipIndex++)
    {
        Ship &ship = ships[shipIndex];
        int length = ship.getLength();

        int firstRow = -1, firstCol = -1;
        int direction = -1; // -1 - undefined, 0 - horizontal, 1 - vertical

        for (int i = 0; i < length; i++)
        {
            board.clearScreen();
            board.showBoard();

            bool validInput = false;
            while (!validInput)
            {
               placeShipElements(row, col, i, ship);

               canShipBePlaced(row, col, i, firstRow, firstCol, direction, validInput, length, ship);


                if (!validInput) {
                    cout << "Please try again." << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                }
                board.clearScreen();
                board.showBoard();
                cout << flush;
            }
        }
        board.occupyCell(row, col);
    }
    board.cancelOccupiedCells(row, col);
}

Board &Player::getBoard()
{
    return board;
    return hiddenBoard;
}

void Player::setPlayerName() {
    cin >> this->playerName; 
}

string Player::getPlayerName() {
    return this->playerName;
}

int Player::getPlayerWins()
{
    return this->playerWins;
}

void Player::addPlayerWin()
{
    this->playerWins++;
}
