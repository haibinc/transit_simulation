// Created by Daniel 05-08-2025

#include "Passenger.h"
#include <iostream>

Passenger::Passenger() : name(""), age(0), destination(""), fare(0.0) {}

Passenger::Passenger(const std::string &name, int age, const std::string &destination,
                     double fare)
    : name(name), age(age), destination(destination), fare(fare) {}

std::string Passenger::getName() const {
    return name;
}

int Passenger::getAge() const {
    return age;
}

std::string Passenger::getDestination() const {
    return destination;
}

double Passenger::getFare() const {
    return fare;
}

void Passenger::displayInfo() const {
    std::cout << "Passenger Name: " << name << "\n"
              << "Age: " << age << "\n"
              << "Destination: " << destination << "\n"
              << "Fare: $" << fare << std::endl;
}
