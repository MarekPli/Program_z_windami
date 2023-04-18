
#ifndef ELEVATORCLASSIC_H
#define ELEVATORCLASSIC_H


#include "elevator.h"

// jestem windą klasyczną, jeżdżę zawsze w tym samym kierunku do końca
// wezwana najpierw skończę swoją drogę, pasażerów odbiorę w drodze powrotnej
class ElevatorClassic :public Elevator
{
private:
    directionKind previous_directory;
public:
    ElevatorClassic(int size) :Elevator(size) {
//        previous_directory = up;
    }
    void execute() override;
};

#endif // ELEVATORCLASSIC_H
