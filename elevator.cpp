

#include "elevator.h"
#include "passenger.h"

Elevator::Elevator(int maxFloor)
{
    this->maxFloor = maxFloor; // zmieniać, obliczyć dla wektora pięter
    minFloor = 0; // można zmienić
    currentFloor = minFloor;
    directory = staying;
    stateOpened = false;
    capacity = 6; // zmieniać
}

void Elevator::informPassengersFloor(){
    for (auto pass : passengers){
        pass->setCurrentFloor(currentFloor);
    }
}

bool Elevator::isInStops(int nr) {
    for (auto i : stops) {
        if (i==nr) {
            return true;
        }
    }
    return false;
}

bool Elevator::isOpenInStop(int nr) {
    if (currentFloor == nr && stateOpened)
        return true;
    return false;
}
bool Elevator::areInStops(int start, int end) {
//    if ( (isInStops(start) ||isOpenInStop(start))
//        && (isInStops(end) || isOpenInStop(end)) )
//        return true;
    StopInOut temp{start,end};
    auto it = stopsInOut.find(temp);
    if (it != stopsInOut.end()) return true;
    return false;
}

void Elevator::removeAndCopyStops(){
    stops.erase(currentFloor);
    for (auto it = stopsInOut.begin(); it != stopsInOut.end(); ) {
        // Sprawdzenie, czy wartość ins jest równa bieżącemu piętru
        if (it->ins == currentFloor) {
            // Wartość outs jest kopiowana do stops
            stops.insert(it->outs);
            // Usunięcie elementu z wektora stopsInOut
            it = stopsInOut.erase(it);
        }
        else {
            // jeśli przedtem usunąłem a jest potrzebne, teraz dopiszę
            if (it->outs != currentFloor)
                stops.insert(it->ins);
            // Przejście do kolejnego elementu (obsługa pętli)
            it++;
        }
    }
}
void Elevator::stopAndServiceFloor() {
    // zatrzymam się tylko gdy będą zamówienia na wyjście
    if (isInStops(currentFloor))
    {
        removeAndCopyStops();
        stateOpened = true;
    }
    else stateOpened = false;
}

bool Elevator::hasAvailableSpace(){
    return static_cast<int>(passengers.size()) < capacity;
}

bool Elevator::isElevatorOpenAndHasSpaceAndHasFinalFloor(int finalF) {
    auto it = stops.find(finalF);
    return stateOpened && hasAvailableSpace() && it != stops.end();
}

void Elevator::boardPassenger(Passenger*p){
    passengers.push_back(p);
}

bool Elevator::exitPassenger(Passenger*pToRemove, int floor){
    if(floor!=currentFloor)
        return true;
    passengers.erase(std::remove_if(passengers.begin(), passengers.end(),
                                    [&](Passenger* p) { return p == pToRemove; }), passengers.end());
    return false;
}

void Elevator::insertStops(int start, int end) {
    // konieczne jednoczesne wstawienie konstruktorem bo inaczej nie wstawi różnych z tym samym start
//    stopsInOut.insert(StopInOut{start,end});
    StopInOut el;
    el.ins = start;
    el.outs = end;
    stopsInOut.insert(el);
    stops.insert(start);
}

void Elevator::goForward(){
    // ruch w dotychczasowym kierunku
    switch (directory) {
    case up:
        if (currentFloor<maxFloor)
            currentFloor++;
        else
            directory = down; // potem można zamienić na postój
        break;
    case down:
        if (currentFloor>minFloor)
            currentFloor--;
        else
            directory = up; // potem można zamienić na postój
        break;
    case staying:
        break;
    default:
        break;
    }
}


