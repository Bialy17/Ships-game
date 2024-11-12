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
    string playerName;
    int playerWins = 0;
    vector<Ship> ships;
public:
    Player();
    ~Player();
    void setShips();
    Board& getBoard();
    void setPlayerName(); 
    string getPlayerName();
    int getPlayerWins();
    void addPlayerWin();
};

#endif