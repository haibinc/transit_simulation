//
// Created by haibi on 4/29/2025.
//

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
private:
    const std::string vin;
    const std::string vehicleType;
    const int totalCapacity;
    int passengersOnBoard;

public:
    //parameterized constructor
    Vehicle(const std::string& vin, const std::string& vehicleType, const int totalCapacity, int passengerOnBoard)
    : vin(vin), vehicleType(vehicleType), totalCapacity(totalCapacity), passengersOnBoard(passengersOnBoard) {}

    virtual ~Vehicle();

    virtual void move() = 0;
    virtual void reportStop() const = 0;

    std::string getVin() const;
    std::string getVehicleType() const;
    int getTotalCapacity() const;
    int getPassengersOnBoard() const;
    void addPassengers(int amount);
    void deletePassengers(int amount);
    void clearBus();

};



#endif //VEHICLE_H
