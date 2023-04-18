#ifndef ELEVATOR_H
#define ELEVATOR_H
#include<set>
#include<vector>
#include<algorithm>
#include<directionkind.h>

class Passenger;// forward declaration

class Elevator
{
    struct StopInOut {
        int ins;
        int outs;
        bool operator<(const StopInOut& other)
            const { return ins < other.ins; }
        bool operator==(const StopInOut& other)
            const { return ins == other.ins && outs == other.outs ; }
    };

protected:
    directionKind directory; // kierunek ruchu: w dół, w górę, nieruchoma
    int currentFloor;
    bool stateOpened; // czy jestem otwarta dla pasażerów
    int minFloor;
    int maxFloor;
    int capacity; // ile osób się zmieści
    std::vector<Passenger*> passengers; // moi pasażerowie
    std::set<StopInOut> stopsInOut; // piętra początkowe i docelowe
    std::set<int> stops; // piętra na których mam się zatrzymać
    void removeAndCopyStops();
    bool hasAvailableSpace();
    void stopAndServiceFloor();
    void goForward();
    bool isInStops(int);
    bool isOpenInStop(int);
    friend class Simulation;
public:
    Elevator(int);
    bool areInStops(int,int);
    void informPassengersFloor();
    bool isElevatorOpenAndHasSpaceAndHasFinalFloor(int);
    void boardPassenger(Passenger*);
    bool exitPassenger(Passenger*, int);// false jeśli pasażer wyszedł
    void insertStops(int, int);
    virtual void execute() = 0; // główna funkcja dla pętli symulacyjnej
    virtual ~Elevator() {
        for (Passenger* passenger: passengers) {
            delete passenger;
        }
    };
};

#endif // ELEVATOR_H
