//
// Created by Kunj on 5/2/2025.
//

#include "Bus.h"
#include <iostream>

void Bus::move()
{
    currentStop = (currentStop + 1) % route.getNumStops();
    reportStop();
}

int Bus::getBusNumber() const { return busNumber; }

int Bus::getCurrentStop() const { return currentStop; }

Route Bus::getRoute() const { return route; }

void Bus::reportStop() const
{
    std::cout << "Bus #" << busNumber << " is at stop " << currentStop << " on route " << route.getRouteName() << std::endl;
}