
#include "elevatorclassic.h"

void ElevatorClassic::execute(){
    if (!stateOpened) {
        goForward();
        // metoda mogła zmienić kierunek, więc zapamiętuję nowy kierunek
        if (directory != staying)
            previous_directory = directory;
    }

    if (!stops.size()) {
        directory = staying; // zamiana na postój
    }
    else {
        if (directory == staying)
            directory = previous_directory;
    }
    // aktualizacja danych dla pasażerów, otwarcie/zamknięcie drzwi
    informPassengersFloor();
    stopAndServiceFloor();
}
