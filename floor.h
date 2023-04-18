
#ifndef FLOOR_H
#define FLOOR_H
#include"passenger.h"


class Floor
{
private:
    std::set<Passenger*> passengers;
    std::set<int> buttons;
    friend class Simulation;
public:
    Floor();
    void receivePassenger(Passenger*);
    bool receiveButton(int);


};

#endif // FLOOR_H
