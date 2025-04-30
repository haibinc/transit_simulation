//
// Created by haibi on 4/29/2025.
//

#include "Vehicle.h"

std::string Vehicle::getVin() const{
    return this->vin;
}

std::string Vehicle::getVehicleType() const {
    return this->vehicleType;
}


int Vehicle::getTotalCapacity() const {
    return this->totalCapacity;
}

int Vehicle::getPassengersOnBoard() const {
    return passengersOnBoard;
}

void Vehicle::addPassengers(int amount) {
    this->passengersOnBoard += amount;
}

void Vehicle::deletePassengers(int amount) {
    this->passengersOnBoard -= amount;
}

void Vehicle::clearBus() {
    this->passengersOnBoard = 0;
}


