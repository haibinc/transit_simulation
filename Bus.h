//
// Created by haibi on 4/29/2025.
//

#ifndef BUS_H
#define BUS_H

#include <string>
#include <vector>
#include "Vehicle.h"
#include "Route.h"
#include "Passenger.h"

class Bus : public Vehicle
{
private:
    const int busNumber;
    int currentStop;
    Route* route;
    std::vector<Passenger*> passengers;

public:
    Bus(const std::string &vin, const std::string &vehicleType,
        int totalCapacity, int passengersOnBoard,
        const int busNumber, int currentStop, Route* route)
        : Vehicle(vin, vehicleType, totalCapacity, passengersOnBoard),
          busNumber(busNumber), currentStop(currentStop), route(route) {};

    void move() override;
    int getBusNumber() const;
    int getCurrentStop() const;
    Route* getRoute() const;
    void reportStop() const;

    std::vector<Passenger*> getPassengers() const;
    int getPassengerCount() const;
    bool isFull() const;
    bool addPassenger(Passenger* passenger);
    bool removePassenger(Passenger* passenger);
};

#endif // BUS_H
