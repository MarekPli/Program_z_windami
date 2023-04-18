
#include "floor.h"
#include<vector>
#include<algorithm>
Floor::Floor()
{
}
void Floor::receivePassenger(Passenger* p){
    passengers.insert(p);
}

