//
// Created by haibi on 4/29/2025.
//

#ifndef BUS_H
#define BUS_H
#include "Vehicle.h"
#include "Route.h"

class Bus : public Vehicle {
private:
    const int busNumber;
    int currentStop;
    Route route;

public:
    Bus(const std::string& vin, const std::string& vehicleType,
       int totalCapacity, int passengersOnBoard,
       const int busNumber, int currentStop, Route route)
       : Vehicle(vin, vehicleType, totalCapacity, passengersOnBoard),
         busNumber(busNumber), currentStop(currentStop), route(route) {};

    void move() override;
    int getBusNumber() const;
    int getCurrentStop() const;
    Route getRoute() const;
};



#endif //BUS_H
