
#ifndef ELEVATORMANAGER_H
#define ELEVATORMANAGER_H
#include<vector>
#include<set>
#include <random>

class Elevator;
class Floor;


class ElevatorManager
{
private:
    std::vector<Elevator*> elevators; // wszystkie windy
    std::vector<Floor*> floors; // wszystkie piętra
    int randomElevator();
    bool isAlreadySigned(int, int);
    void setStops(int, int);
    friend class Simulation;
public:
    ElevatorManager(std::vector<Elevator*>, std::vector<Floor*>);
    ~ElevatorManager();
    void signal(int, int);
};

#endif // ELEVATORMANAGER_H
