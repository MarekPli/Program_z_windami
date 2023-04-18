
#ifndef ELEVATORMODERN_H
#define ELEVATORMODERN_H


#include "elevator.h"

// jestem windą modern, mogę zmieniać kierunek
// gdy jestem pusta, to pojadę w kierunku piętra, które mnie wezwie
class ElevatorModern: public Elevator
{
private:
    void modifyDirection();
public:
    ElevatorModern(int size) :Elevator(size) {}
    void execute() override;
};

#endif // ELEVATORMODERN_H
