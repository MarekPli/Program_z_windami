
#ifndef ELEVATORDESTINATIONCONTROL_H
#define ELEVATORDESTINATIONCONTROL_H


#include "elevator.h"

// jestem windą pospieszną, dowożę bez zbędnych przystanków
// uwzględnię zamówienie nowego pasażera dopiero gdy poprzedni dojedzie
class ElevatorDestinationControl: public Elevator
{
private:
    int myFinalStop;
    int myStartingStop;
public:
    ElevatorDestinationControl(int size) :Elevator(size) {}
    void execute() override;
};

#endif // ELEVATORDESTINATIONCONTROL_H
