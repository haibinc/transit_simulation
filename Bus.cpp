//
// Created by Kunj on 5/2/2025.
//

#include "Bus.h"
#include <iostream>
#include <algorithm>

Bus::~Bus() {
    for (Passenger* p : passengers)
        delete p;
}

void Bus::move()
{
    currentStop = (currentStop + 1) % route->getNumStops();
    reportStop();
}

int Bus::getBusNumber() const { return busNumber; }

int Bus::getCurrentStop() const { return currentStop; }

Route* Bus::getRoute() const { return route; }

void Bus::reportStop() const
{
    std::cout << "Bus #" << busNumber << " is at stop " << currentStop << " on route " << route->getRouteName() << std::endl;
}

std::vector<Passenger*> Bus::getPassengers() const { return passengers; }

int Bus::getPassengerCount() const { return passengers.size(); }

bool Bus::isFull() const { return passengers.size() >= getTotalCapacity(); }

bool Bus::addPassenger(Passenger* passenger)
{
    if (!isFull())
    {
        passengers.push_back(passenger);
        addPassengers(1);
        return true;
    }
    return false;
}

bool Bus::removePassenger(Passenger* passenger)
{
    std::vector<Passenger*>::iterator it = std::remove(passengers.begin(), passengers.end(), passenger);
    if (it != passengers.end())
    {
        passengers.erase(it);
        deletePassengers(1);
        return true;
    }
    return false;
}

