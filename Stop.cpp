//
// Created by Habin on 4/29/2025.
// Updated by Kunj on 5/2/2025.
//

#include "Stop.h"

Stop::Stop() : stopName(""), nextStop(nullptr), prevStop(nullptr), timeToNextStop(0) {}

Stop *Stop::getNextStop() const { return nextStop; }

Stop *Stop::getPrevStop() const { return prevStop; }

int Stop::getTimeToNextStop() const { return timeToNextStop; }

const std::string &Stop::getStopName() const { return stopName; }

std::vector<Passenger*> Stop::getPassengers() const { return passengers; }

void Stop::setStopName(const std::string &name) { stopName = name; }

void Stop::setNextStop(Stop *stop) { nextStop = stop; }

void Stop::setPrevStop(Stop *stop) { prevStop = stop; }

void Stop::setTimeToNextStop(int time) { timeToNextStop = time; }

void Stop::addPassenger(Passenger* passenger) { passengers.push_back(passenger); }

void Stop::removePassenger(Passenger* passenger) {
    std::vector<Passenger*>::iterator it = std::remove(passengers.begin(), passengers.end(), passenger);
    if (it != passengers.end()) {
        passengers.erase(it, passengers.end());
    }
}