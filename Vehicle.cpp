//
// Created by Haibi on 4/29/2025.
// Updated by Kunj on 5/2/2025.
//

#include "Vehicle.h"

Vehicle::~Vehicle() {}

std::string Vehicle::getVin() const { return vin; }

std::string Vehicle::getVehicleType() const { return vehicleType; }

int Vehicle::getTotalCapacity() const { return totalCapacity; }

int Vehicle::getPassengersOnBoard() const { return passengersOnBoard; }

void Vehicle::addPassengers(int amount)
{
    passengersOnBoard += amount;
    if (passengersOnBoard > totalCapacity)
        passengersOnBoard = totalCapacity;
}

void Vehicle::deletePassengers(int amount)
{
    passengersOnBoard -= amount;
    if (passengersOnBoard < 0)
        passengersOnBoard = 0;
}

void Vehicle::clearBus() { passengersOnBoard = 0; }