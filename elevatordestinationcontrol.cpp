
#include "elevatordestinationcontrol.h"

void ElevatorDestinationControl::execute(){
    if (!stateOpened) {
        goForward();
    }

    if (!stops.size()) {
        directory = staying; // zamiana na postój
    }
    else {
        if (directory == staying)
            ;
    }
    // aktualizacja danych dla pasażerów, otwarcie/zamknięcie drzwi
    informPassengersFloor();
    stopAndServiceFloor();
}
