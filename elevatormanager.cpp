
#include "elevatormanager.h"
#include"elevator.h"
#include"floor.h"

ElevatorManager::ElevatorManager(std::vector<Elevator*> elevators,
                                 std::vector<Floor*> floors)
{
    this->elevators = elevators;
    this->floors = floors;
}

bool ElevatorManager::isAlreadySigned(int start, int end) {
    //    szukaj pary przystanków w tej samej windzie
    if (start == end) return true;
    for (std::size_t i=0; i<elevators.size(); i++) {
        //        if ((elevators[i]->isInStops(start)
        //             || elevators[i]->isOpenInStop(start))
        //            && elevators[i]->isInStops(end))
        if (elevators[i]->areInStops(start,end))
            return true;
    }
    return false;
}

int ElevatorManager::randomElevator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, elevators.size() - 1);
    int index = dis(gen);
    return index;
}
void ElevatorManager::setStops(int start, int end) {
// wybrać windę (tu mogą być różne algorytmy, np. najbliższą)
// wstawić do windy dwa stopy
// winda sama zadziała z resztą: ruszeniem i ew. zmianą kierunku
//wariant z losowaniem:
    int idx = randomElevator();
    elevators[idx]->insertStops(start,end);

}

void ElevatorManager::signal(int start, int end) {
    // nie uruchamiam nowej windy gdy już jakaś jedzie
    if (isAlreadySigned(start, end)) return;
    setStops(start, end);
}
ElevatorManager::~ElevatorManager() {
    for (Elevator* elevator: elevators) {
        delete elevator;
    }
    for (Floor * floor: floors) {
        delete floor;
    }
}

