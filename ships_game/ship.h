#ifndef SHIP_H
#define SHIP_H
#include <string>
using namespace std;
class Ship {
private:
    int lengthOfShip;
    string nameOfShip;
public:
    Ship(int lengthOfShip, const string& nameOfShip);
    ~Ship();
    int getLength() const;
    string getName() const;
};
#endif