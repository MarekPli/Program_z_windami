
#include "elevatormodern.h"

void ElevatorModern::modifyDirection() {
    if (directory==staying) { // tylko gdy puste; metodę się wywołuje tylko pod tym warunkiem
        auto it = stops.begin();
        int first_stop = *it;
        it = stops.end();
        int last_stop = *(--it);
        // jeśli poniżej/powyżej, po prostu w kierunku przystanków
        if (currentFloor > last_stop)
            directory = down;
        else if (currentFloor < first_stop)
            directory = up;
        else {
            //w przeciwnym wypadku w kierunku mniejszej ilości przystanków
            int more_than = 0;
            int less_than = 0;
            for (auto i : stops) {
                if (i<currentFloor)
                    more_than++;
                else less_than++;
            }
            if (more_than > less_than)
                directory = down;
            else directory = up;
        }
    }
}


void ElevatorModern::execute(){
    if (!stateOpened)
        goForward();
    if (!stops.size())
        directory=staying; // zamiana na postój
    else modifyDirection();
    // aktualizacja danych dla pasażerów, otwarcie/zamknięcie drzwi
    informPassengersFloor();
    stopAndServiceFloor();
}

