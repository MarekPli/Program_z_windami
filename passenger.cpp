
#include "passenger.h"
#include "elevator.h"
#include "elevatormanager.h"
#include"floor.h"
Passenger::Passenger(int currentFloor, int finalFloor,
                     std::vector<Floor*> floors,
                     std::vector<Elevator*> elevators,
                     ElevatorManager *eManager)
{
    this->currentFloor = currentFloor;
    this->finalFloor = finalFloor;
    this->floors = floors;
    this->elevators = elevators;
    this->eManager = eManager;
    inElevator = false;
    elevatorId = -1;
    buttonPressed = false;
}

void Passenger::setCurrentFloor(int currentFloor) {
    this->currentFloor = currentFloor;
}

void Passenger::pressButton(){
    if (inElevator) return;
    if (currentFloor == finalFloor) return;
    eManager->signal(currentFloor, finalFloor);
}
int Passenger::searchElevators(){
    for (std::size_t i=0; i<elevators.size(); i++) {
        if (elevators[i]->isElevatorOpenAndHasSpaceAndHasFinalFloor(finalFloor))
            return i;
    }
    return -1;
}

void Passenger::execute() {

    //jeśli jestem w windzie, mogę wysiąść
    if (inElevator) {
        // wysiadam jeśli jestem u celu
        inElevator = elevators[elevatorId]->exitPassenger(this, finalFloor);
        return;
    }


    // jeśli nie jestem w windzie, mogę
    // - wezwać windę (gdy niewezwana)
    // - wsiąść do wybranej windy
    // - nic nie robić (zniknąć), bo już jestem na piętrze docelowym

    // nie ma mnie w windzie:
    if (!inElevator) {
        if (currentFloor == finalFloor)
            return;
        // wsiadam do pierwszej dostępnej windy
        elevatorId = searchElevators();
        if (elevatorId >=0) {
            elevators[elevatorId]->boardPassenger(this);
            inElevator = true;
        }
        pressButton(); // wciskam guzik swojego piętra docelowego gdy niewciśnięty
    }
}

Passenger::~Passenger(){
    for (Elevator* elevator: elevators) {
        delete elevator;
    }

    for (Floor* floor: floors) {
        delete floor;
    }
    delete eManager;
}
