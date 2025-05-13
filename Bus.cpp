//
// Created by Kunj on 5/2/2025.
//

#include "Bus.h"
#include <iostream>
#include <algorithm>
#include <ostream>

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

StopNode* getCurrentStopNode(Route* route, int i) {
    int counter = 0;
    StopNode* current = route->getHead();
    while (current)
    {
        if (counter == i) {
            return current;
        }
        current = current->getNextStopNode();
        counter++;
    }
    return nullptr;
}

void Bus::reportStop() const
{
    std::cout << *this << " is at " << *(getCurrentStopNode(getRoute(), currentStop)->getStop()) << " on " << *route << "" << std::endl;
}

void Bus::progress() {
    int counter = 0;
    StopNode* current = getCurrentStopNode(getRoute(), currentStop);

    if (current) {
        routeProgress++;
        if (routeProgress >= current->getTimeToNextStop()) {
            routeProgress = 0;
            move();
        }
    }

    
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

int Bus::getCapacity() const {
    return this->getTotalCapacity();
}


std::ostream& operator<<(std::ostream& strm, const Bus& bus) {
    strm << "Bus(VIN:" << bus.getVin() << ", NUM:" << bus.getBusNumber() << ", CAP:" << bus.getTotalCapacity() << ", ROUT:" << bus.getRoute()->getRouteName() << ")";
    return strm;
}

bool operator<(const Bus& lhs, const Bus& rhs) {
    return lhs.getVin() < rhs.getVin();
}

bool operator>(const Bus& lhs, const Bus& rhs) {
    return rhs.getVin() > lhs.getVin();
}

bool operator==(const Bus& lhs, const Bus& rhs) {
    return lhs.getVin() == rhs.getVin();
}

bool operator==(const std::string& lhs, Bus& rhs) {
    return lhs == rhs.getVin();
}

bool operator==(const Bus& lhs, const std::string& rhs) {
    return lhs.getVin() == rhs;
}

bool operator<(const std::string& lhs, const Bus& rhs) {
    return lhs < rhs.getVin();
}

bool operator<(const Bus& lhs, const std::string& rhs) {
    return lhs.getVin() < rhs;
}

bool operator>(const std::string& lhs, const Bus& rhs) {
    return lhs > rhs.getVin();
}

bool operator>(const Bus& lhs, const std::string& rhs) {
    return lhs.getVin() > rhs;
}

