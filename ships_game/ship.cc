#include "ship.h"
#include <string>
using namespace std;

Ship::Ship(int lengthOfShip, const string& nameOfShip)
{
    this -> lengthOfShip = lengthOfShip;
    this -> nameOfShip = nameOfShip;
}

Ship::~Ship()
{
}

int Ship::getLength() const
{
    return lengthOfShip;
}

string Ship::getName() const
{
    return nameOfShip;
}
