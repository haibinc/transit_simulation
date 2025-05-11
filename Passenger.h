// Created by Daniel 05-08-2025

#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

class Passenger {
    private:
        std::string name;
        int age;
        std::string destination;
        double fare;
    
    public:
        Passenger();
        Passenger(const std::string &name, int age, const std::string &destination,
                 double fare);
            
        std::string getName() const;
        int getAge() const;
        std::string getDestination() const;
        double getFare() const;

        void displayInfo() const;
};

#endif