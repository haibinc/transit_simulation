//
// Created by Habin on 4/29/2025.
// Updated by Kunj on 5/2/2025.
//

#include <algorithm>
#include <ostream>
#include "Stop.h"

const std::string &Stop::getStopName() const { return stopName; }

std::vector<Passenger*> Stop::getPassengers() const { return passengers; }

void Stop::setStopName(const std::string &name) { stopName = name; }

void Stop::addPassenger(Passenger* passenger) { passengers.push_back(passenger); }

void Stop::removePassenger(Passenger* passenger) {
    std::vector<Passenger*>::iterator it = std::remove(passengers.begin(), passengers.end(), passenger);
    if (it != passengers.end()) {
        passengers.erase(it, passengers.end());
    }
}

std::ostream& operator<<(std::ostream& strm, const Stop& stop) {
    strm << "Stop(NAME:" << stop.getStopName() << ")";
    return strm;
}

bool operator<(const Stop& lhs, const Stop& rhs) {
    return lhs.getStopName() < rhs.getStopName();
}

bool operator>(const Stop& lhs, const Stop& rhs) {
    return rhs.getStopName() > lhs.getStopName();
}

bool operator==(const Stop& lhs, const Stop& rhs) {
    return lhs.getStopName() == rhs.getStopName();
}

bool operator==(const std::string& lhs, Stop& rhs) {
    return lhs == rhs.getStopName();
}

bool operator==(const Stop& lhs, const std::string& rhs) {
    return lhs.getStopName() == rhs;
}

bool operator<(const std::string& lhs, const Stop& rhs) {
    return lhs < rhs.getStopName();
}

bool operator<(const Stop& lhs, const std::string& rhs) {
    return lhs.getStopName() < rhs;
}

bool operator>(const std::string& lhs, const Stop& rhs) {
    return lhs > rhs.getStopName();
}

bool operator>(const Stop& lhs, const std::string& rhs) {
    return lhs.getStopName() > rhs;
}