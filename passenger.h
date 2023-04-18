#ifndef PASSENGER_H
#define PASSENGER_H
#include<set>
#include<vector>


class Elevator; // forward declaration
class ElevatorManager; // forward declaration
class Floor;// albo: deklaracja wstępna

class Passenger
{
private:
    int currentFloor; // piętro na którym jest pasażer
    int finalFloor; // jeśli puste, to pasażer "dotarł do celu" (zostanie usunięty z programu)
    bool inElevator; // pasażer może być w windzie albo nie
    std::vector<Elevator*> elevators; // wszystkie windy
    int elevatorId; // winda w której jest pasażer
    std::vector<Floor*> floors; // wszystkie piętra
//    std::set<Passenger*> peopleOnTheFloor; // inni na piętrze
    ElevatorManager *eManager;
    void pressButton();
    int searchElevators();
    bool buttonPressed;
    friend class Simulation;

public:
    Passenger(int,int,std::vector<Floor*>, std::vector<Elevator*>, ElevatorManager*);
    ~Passenger();
    void setCurrentFloor(int); // wywołuje to winda lub symulator na początku)
    void execute(); // główna funkcja dla pętli symulacyjnej
};

#endif // PASSENGER_H
