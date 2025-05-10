//
// Created by Misha on 5/2/2025.
//

/*
 g++ -fdiagnostics-color=always -g C:/Users/misha/Documents/GitHub/transit_simulation/main.cpp C:/Users/misha/Documents/GitHub/transit_simulation/Route.cpp C:/Users/misha/Documents/GitHub/transit_simulation/Bus.cpp C:/Users/misha/Documents/GitHub/transit_simulation/Vehicle.cpp C:/Users/misha/Documents/GitHub/transit_simulation/Stop.cpp C:/Users/misha/Documents/GitHub/transit_simulation/TransitManager.cpp -o C:/Users/misha/Documents/GitHub/transit_simulation/main.exe
*/

// Library imports
#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
// Our imports
#include "Route.h"
#include "Stop.h"
#include "Bus.h"
#include "TransitManager.h"

enum Actions { 
    PRINT_BUSES, PRINT_ROUTES, PRINT_STOPS_IN_ROUTE, // Print actions 
    ADD_BUS, ADD_ROUTE, ADD_STOP_TO_ROUTE, // Add actions
    QUIT // Last element also used for bound checks
};

std::vector<Bus*> registeredBuses;
std::vector<Route*> registeredRoutes;

void promptActions() {
    std::cout << "Type a number corresponding with any of the following actions:\n";
    // Prints
    std::cout << "(" << PRINT_BUSES << ") prints all buses that are controlled by this manager.\n";
    std::cout << "(" << PRINT_ROUTES << ") prints all routes that are controlled by this manager.\n";
    std::cout << "(" << PRINT_STOPS_IN_ROUTE << ") prints all stops that are controlled by this manager.\n";
    // Adds
    std::cout << "(" << ADD_BUS << ") adds a bus to the list of registered buses.\n";
    std::cout << "(" << ADD_ROUTE << ") adds a route to the list of registered routes.\n";
    std::cout << "(" << ADD_STOP_TO_ROUTE << ") adds a stop to the list of registered stops.\n";
    // Quit
    std::cout << "(" << QUIT << ") quits the transit manager.\n";
}

int getUserAction() {
    int input = -1;

    // Verify user input
    for (bool first = true; input < 0 || input > QUIT; std::cin >> input, first = false) {
        if (!first) {
            std::cout << "Invalid input! Please make sure you input is between 0 and " << (QUIT) << "!\n";
        }

        promptActions();
    }

    return input;
}

template <typename T>
void printVector(const std::vector<T>& vector) {
    std:: cout << "[";
    for (typename std::vector<T>::const_iterator it = vector.begin(); it != vector.end(); ++it) {
        if (Bus* bus = dynamic_cast<Bus*>(*it)) {
            std::cout << bus->getBusNumber();
        } else if (Route* route = dynamic_cast<Route*>(*it)) {
            std::cout << route->getRouteName();
        } else if (Stop* stop = dynamic_cast<Stop*>(*it)) {
            std::cout << stop->getStopName();
        }
        if (it < vector.end() - 1) {
            std::cout << ", ";
        }
    }
    std:: cout << "]\n";
}

Route* routeBinarySearch(std::string& name) {
    return routeBinarySearch(name, registeredRoutes.begin(), registeredRoutes.end());
}

Route* routeBinarySearch(std::string& name, std::vector<Route*>::const_iterator start, std::vector<Route*>::const_iterator end) {
    if (start >= end)
        return nullptr;

    std::vector<Route*>::const_iterator middle = start + (end - start) / 2;

    if ((*middle)->getRouteName() == name) {
        return *middle;
    } else if ((*middle)->getRouteName() < name) {
        return routeBinarySearch(name, middle + 1, end);
    } else {
        return routeBinarySearch(name, start, middle);
    }
}

void addBus() {
    // str vin, str type, int cap, int pas, int busNum, int currStop, Route* route
    std:: cout << "Enter a bus vin:\n";
    std::string vin;
    std::cin >> vin;

    // Should there be an input for vehicle type??? Wouldn't all buses have the same type? City bus?
    std::string vehicleType = "City bus";

    std::cout << "Enter bus capacity:\n";
    int capacity;
    while (!(std::cin >> capacity)) {
        std::cout << "Enter bus capacity:\n";
    }

    std::cout << "Enter a bus number:\n";
    int busNumber;
    while (!(std::cin >> busNumber)) {
        std::cout << "Enter a bus number:\n";
    }

    int currentStop = 0;

    std::cout << "Enter the route this bus should take:\n";
    std::string routeName;
    getline(std::cin, routeName);


}

void addRoute() {
    // str name
}

void beginPromptLoop() {
    std::cout << "\nTransitManager started!\n";

    for (int userAction = getUserAction(); userAction != QUIT; userAction = getUserAction()) {
        switch (userAction) {
            case PRINT_BUSES:
                printVector(registeredBuses);
                break;
            case PRINT_ROUTES:
                printVector(registeredRoutes);
                break;
            case PRINT_STOPS_IN_ROUTE:
                std::cout << "FINISH ME!\n";
                break;
            case ADD_BUS:
            case ADD_ROUTE:
            case ADD_STOP_TO_ROUTE:
                std::cout << "Not implemented yet!\n";
                break;
            default:
                std::cout << "Unknown action!\n";
                break;
        }
    }

    std::cout << "The transit manager has been quit! Goodbye!\n";
}

