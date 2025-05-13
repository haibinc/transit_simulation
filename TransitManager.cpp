//
// Created by Misha on 5/2/2025.
//

/*
g++ -fdiagnostics-color=always -g C:/Users/misha/Documents/GitHub/transit_simulation/main.cpp C:/Users/misha/Documents/GitHub/transit_simulation/Route.cpp C:/Users/misha/Documents/GitHub/transit_simulation/Bus.cpp C:/Users/misha/Documents/GitHub/transit_simulation/Vehicle.cpp C:/Users/misha/Documents/GitHub/transit_simulation/Stop.cpp C:/Users/misha/Documents/GitHub/transit_simulation/TransitManager.cpp C:/Users/misha/Documents/GitHub/transit_simulation/StopNode.cpp -o C:/Users/misha/Documents/GitHub/transit_simulation/main.exe 
*/

// Library imports
#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
#include <functional>
#include <algorithm>
#include <limits>
#include <functional>
#include <sstream>
#include <fstream>
#include <random>
#include <array>
#include <unordered_map>
#include <cmath>
#include <map>
#include <thread>
#include <chrono>
// Our imports
#include "Route.h"
#include "Stop.h"
#include "Bus.h"
#include "TransitManager.h"

enum Actions { 
     // Print actions 
    PRINT_BUSES, PRINT_ROUTES, PRINT_STOPS, PRINT_STOPS_IN_ROUTE,
    // Add actions
    ADD_BUS, ADD_ROUTE, ADD_STOP, 
    // Remove actions
    REMOVE_BUS, REMOVE_ROUTE, REMOVE_STOP,
    // Modify actions
    ADD_ROUTE_STOP_BEGIN, ADD_ROUTE_STOP_END, ADD_ROUTE_STOP_BEFORE, ADD_ROUTE_STOP_AFTER, REMOVE_ROUTE_STOP, 
    // IO
    SAVE_REG, LOAD_REG,
    // Sim
    BEGIN_SIM,
    // Last element also used for bound checks
    QUIT
};

std::vector<Bus*> registeredBuses;
std::vector<Route*> registeredRoutes;
std::vector<Stop*> registeredStops;

void promptActions() {
    std::cout << "Type a number corresponding with any of the following actions:" << std::endl;
    std::cout << "---- PRINT ----" << std::endl;
    std::cout << "(" << PRINT_BUSES << ") prints all buses that are controlled by this manager." << std::endl;
    std::cout << "(" << PRINT_ROUTES << ") prints all routes that are controlled by this manager." << std::endl;
    std::cout << "(" << PRINT_STOPS << ") prints all stops that are controlled by this manager." << std::endl;
    std::cout << "(" << PRINT_STOPS_IN_ROUTE << ") prints all the stops that are on a route." << std::endl;
    std::cout << "---- ADD ----" << std::endl;
    std::cout << "(" << ADD_BUS << ") adds a bus to the list of registered buses." << std::endl;
    std::cout << "(" << ADD_ROUTE << ") adds a route to the list of registered routes." << std::endl;
    std::cout << "(" << ADD_STOP << ") adds a stop to the list of registered stops." << std::endl;
    std::cout << "---- REMOVE ----" << std::endl;
    std::cout << "(" << REMOVE_BUS << ") removes a bus from the list of registered buses." << std::endl;
    std::cout << "(" << REMOVE_ROUTE << ") removes a route from the list of registered routes." << std::endl;
    std::cout << "(" << REMOVE_STOP << ") removes a stop from the list of registered stops." << std::endl;
    std::cout << "---- MODIFY ----" << std::endl;
    std::cout << "(" << ADD_ROUTE_STOP_BEGIN << ") prepends a stop to an already registered route." << std::endl;
    std::cout << "(" << ADD_ROUTE_STOP_END << ") appends a stop to an already registered route." << std::endl;
    std::cout << "(" << ADD_ROUTE_STOP_BEFORE << ") inserts a stop behind another stop in an already registered route." << std::endl;
    std::cout << "(" << ADD_ROUTE_STOP_AFTER << ") inserts a stop after another stop in an already registered route" << std::endl;
    std::cout << "(" << REMOVE_ROUTE_STOP << ") removes a stop from an already registered route." << std::endl;
    std::cout << "---- IO ----" << std::endl;
    std::cout << "(" << SAVE_REG << ") saves current registry to a file." << std::endl;
    std::cout << "(" << LOAD_REG << ") loads registry from file." << std::endl;
    std::cout << "---- SIMULATE ----" << std::endl;
    std::cout << "(" << BEGIN_SIM << ") begins the simulation of the transit manager using all buses, routes, and stops." << std::endl;
    // End
    std::cout << "(" << QUIT << ") quits the transit manager." << std::endl;
}

int getValidInt() {
    int input = 0;
    std::string line;
    
    while (true) {
        std::getline(std::cin, line);
        
        std::istringstream stream(line);
        if (stream >> input && stream.eof()) {
            break;
        } else {
            std::cout << "Invalid input! Please enter a valid integer." << std::endl;
        }
    }

    return input;
}

std::string getSpacelessString() {
    std::string input;

    while (true) {
        std::getline(std::cin, input);

        if (!input.empty() && std::none_of(input.begin(), input.end(), ::isspace)) {
            break;
        } else {
            std::cout << "Invalid input! Please enter a word without spaces." << std::endl;
        }
    }

    return input;
}


std::string getNonEmptyString() {
    std::string input;

    while (true) {
        std::getline(std::cin, input);

        if (!input.empty()) {
            break;
        } else {
            std::cout << "Input cannot be empty. Please try again." << std::endl;
        }
    }

    return input;
}

int getUserAction() {
    int input = -1;

    // Verify user input
    for (bool first = true; input < 0 || input > QUIT; first = false, input = getValidInt()) {
        if (!first) {
            std::cout << "Invalid input! Please make sure you input is between 0 and " << (QUIT) << "!" << std::endl;
        }

        promptActions();
    }

    return input;
}

template <typename T> 
void printVector(const std::vector<T*>& vector) {
    for (typename std::vector<T*>::const_iterator it = vector.begin(); it != vector.end(); ++it) {
        std::cout << **it;
        if (it < vector.end() - 1) {
            std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
T* binarySearch(const std::string& name, typename std::vector<T*>::const_iterator start, typename std::vector<T*>::const_iterator end) {
    if (start >= end)
        return nullptr;

    typename std::vector<T*>::const_iterator middle = start + (end - start) / 2;

    if (**middle == name) {
        return *middle;
    } else if (**middle < name) {
        return binarySearch<T>(name, middle + 1, end);
    } else {
        return binarySearch<T>(name, start, middle);
    }
}

Bus* busBinarySearch(const std::string& name) {
    return binarySearch<Bus>(name, registeredBuses.cbegin(), registeredBuses.cend());
}

Route* routeBinarySearch(const std::string& name) {
    return binarySearch<Route>(name, registeredRoutes.cbegin(), registeredRoutes.cend());
}

Stop* stopBinarySearch(const std::string& name) {
    return binarySearch<Stop>(name, registeredStops.cbegin(), registeredStops.cend());
}

template <typename T>
void binaryInsert(std::vector<T*>& vec, T* newItem) {
    typename std::vector<T*>::iterator it = std::lower_bound(vec.begin(), vec.end(), newItem, [](T* a, T* b) { return *a < *b; });
    vec.insert(it, newItem);
}

void busBinaryInsert(Bus* bus) {
    binaryInsert(registeredBuses, bus);
}

void routeBinaryInsert(Route* route) {
    binaryInsert(registeredRoutes, route);
}

void stopBinaryInsert(Stop* stop) {
    binaryInsert(registeredStops, stop);
}

template <typename T>
T* getValid(typename std::vector<T*>& registry, bool spaceless) {
    std::cout << "Registry:" << std::endl;
    printVector(registry);

    std::string search = spaceless ? getSpacelessString() : getNonEmptyString();
    T* item = binarySearch<T>(search, registry.cbegin(), registry.cend());
    while (item == nullptr) {
        std::cout << "Please enter a name:" << std::endl;
        search = spaceless ? getSpacelessString() : getNonEmptyString();
        item = binarySearch<T>(search, registry.cbegin(), registry.cend());
    }

    return item;
}

Bus* getValidBus() {
    return getValid<Bus>(registeredBuses, true);
}

Route* getValidRoute() {
    return getValid<Route>(registeredRoutes, true);
}

Stop* getValidStop() {
    return getValid<Stop>(registeredStops, false);
}

void addBus() {
    if (registeredRoutes.size() == 0) {
        std::cout << "There must be at least one route before you can register a new bus!" << std::endl;
        return;
    }

    // str vin, str type, int cap, int pas, int busNum, int currStop, Route* route
    std:: cout << "Enter a bus vin:" << std::endl;
    std::string vin = getSpacelessString();
    while (busBinarySearch(vin) != nullptr) {
        std::cout << "A bus with this vin is already registered! Please try again." << std::endl;
        vin = getSpacelessString();
    }

    // Should there be an input for vehicle type??? Wouldn't all buses have the same type? City bus?
    std::string vehicleType = "City bus";

    std::cout << "Enter bus capacity:" << std::endl;
    int capacity = getValidInt();

    int passengers = 0;

    std::cout << "Enter a bus number:" << std::endl;
    int busNumber = getValidInt();

    int currentStop = 0;

    std::cout << "Enter the route this bus takes:" << std::endl;
    Route* route = getValidRoute();

    busBinaryInsert(new Bus(vin, vehicleType, capacity, passengers, busNumber, currentStop, route));
}

void addRoute() {
    std::cout << "Enter the name of the route you want to create:" << std::endl;
    std::string routeName = getSpacelessString();
    while (routeBinarySearch(routeName) != nullptr) {
        std::cout << "A route with this name is already registered! Please try again." << std::endl;
        routeName = getSpacelessString();
    }

    routeBinaryInsert(new Route(routeName));
}

void addStop() {
    std::cout << "Enter the name of the stop you want to register:" << std::endl;
    std::string stopName = getNonEmptyString();
    while (stopBinarySearch(stopName) != nullptr) {
        std::cout << "A stop with this name is already registered! Please try again." << std::endl;
        stopName = getNonEmptyString();
    }

    stopBinaryInsert(new Stop(stopName));
}

void printRouteStops() {
    if (registeredRoutes.size() == 0) {
        std::cout << "There are currently no registered routes!" << std::endl;
        return;
    }

    std::cout << "Enter a route name:" << std::endl;
    Route* route = getValidRoute();

    route->printRouteForward();
}

template <typename T>
void deleteItem(std::vector<T*>& registry, T* item) {
    typename std::vector<T*>::iterator it = std::find(registry.begin(), registry.end(), item);
    if (it != registry.end()) {
        registry.erase(it);
        delete item;
    }
}

template <typename T>
void deleteVector(std::vector<T*>& registry) {
    typename std::vector<T*>::iterator it = registry.begin();
    for (; it < registry.end(); ++it) {
        delete *it;
    }
    registry.clear();
}

void removeBus() {
    deleteItem(registeredBuses, getValidBus());
}

void removeRoute() {
    Route* route = getValidRoute();
    
    registeredBuses.erase( // ???
        std::remove_if(
            registeredBuses.begin(),
            registeredBuses.end(),
            [route](Bus* bus) {
                if (bus->getRoute() == route) {
                    delete bus;
                    return true;
                }
                return false;
            }
        ),
        registeredBuses.end()
    );

    deleteItem(registeredRoutes, route);
}

void removeStop() {
    Stop* stop = getValidStop();

    for (std::vector<Route*>::iterator it = registeredRoutes.begin(); it < registeredRoutes.end(); ++it) {
        if ((*it)->stopExist(stop->getStopName())) {
            (*it)->removeStop(stop->getStopName());
        }
    }

    deleteItem(registeredStops, stop);
}

void prependStopToRoute() {
    std::cout << "Enter the name of the route you'd like to modify:" << std::endl;
    Route* route = getValidRoute();

    std::cout << "Enter the name of the stop you'd like to prepend to this route:" << std::endl;
    Stop* stop = getValidStop();

    route->addStopToFront(stop);
}

void appendStopToRoute() {
    std::cout << "Enter the name of the route you'd like to modify:" << std::endl;
    Route* route = getValidRoute();

    std::cout << "Enter the name of the stop you'd like to append to this route:" << std::endl;
    Stop* stop = getValidStop();

    route->addStopToBack(stop);
}

void addStopBeforeToRoute() {
    std::cout << "Enter the name of the route you'd like to modify:" << std::endl;
    Route* route = getValidRoute();

    std::cout << "Enter the name of the stop you'd like to insert to this route:" << std::endl;
    Stop* stop = getValidStop();

    std::cout << "Enter the name of the stop you'd like to insert the new stop behind in this route:" << std::endl;
    Stop* before = getValidStop();

    route->addStopBefore(stop, before->getStopName());
}

void addStopAfterToRoute() {
    std::cout << "Enter the name of the route you'd like to modify:" << std::endl;
    Route* route = getValidRoute();

    std::cout << "Enter the name of the stop you'd like to insert to this route:" << std::endl;
    Stop* stop = getValidStop();

    std::cout << "Enter the name of the stop you'd like to insert the new stop ahead of in this route:" << std::endl;
    Stop* before = getValidStop();

    route->addStopAfter(stop, before->getStopName());
}

void removeStopFromRoute() {
    std::cout << "Enter the name of the route you'd like to modify:" << std::endl;
    Route* route = getValidRoute();

    std::cout << "Enter the name of the stop you'd like to remove from this route:" << std::endl;
    Stop* stop = getValidStop();

    route->removeStop(stop->getStopName());
}

void saveRegistry(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    // Save stops
    file << "STOPS\n";
    for (Stop* stop : registeredStops) {
        file << stop->getStopName() << '\n';
    }

    // Save routes
    file << "\nROUTES\n";
    for (Route* route : registeredRoutes) {
        file << route->getRouteName() << ':';
        StopNode* node = route->getHead();
        while (node) {
            file << node->getStop()->getStopName();
            node = node->getNextStopNode();
            if (node) file << ',';
        }
        file << '\n';
    }

    // Save buses
    file << "\nBUSES\n";
    for (Bus* bus : registeredBuses) {
        file << bus->getVin() << ',' << bus->getVehicleType() << ',' << bus->getCapacity() << ',' << bus->getPassengerCount()
             << ',' << bus->getBusNumber() << ',' << bus->getCurrentStop() << ',' << bus->getRoute()->getRouteName() << '\n';
    }

    file.close();
    std::cout << "Saved successfully to " << filename << std::endl;
}


void loadRegistry(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    deleteVector(registeredBuses);
    deleteVector(registeredRoutes);
    deleteVector(registeredStops);

    std::string line, section;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line == "STOPS" || line == "ROUTES" || line == "BUSES") {
            section = line;
            continue;
        }

        if (section == "STOPS") {
            stopBinaryInsert(new Stop(line));
        } else if (section == "ROUTES") {
            auto colon = line.find(':');
            std::string routeName = line.substr(0, colon);
            auto* route = new Route(routeName);
            std::string stopsLine = line.substr(colon + 1);
            std::stringstream ss(stopsLine);
            std::string stopName;
            while (std::getline(ss, stopName, ',')) {
                Stop* stop = stopBinarySearch(stopName);
                if (stop) route->addStopToBack(stop);
            }
            routeBinaryInsert(route);
        } else if (section == "BUSES") {
            std::stringstream ss(line);
            std::string vin, type, routeName;
            int cap, pas, num, currStop;
            std::getline(ss, vin, ',');
            std::getline(ss, type, ',');
            ss >> cap;
            ss.ignore();
            ss >> pas;
            ss.ignore();
            ss >> num;
            ss.ignore();
            ss >> currStop;
            ss.ignore();
            std::getline(ss, routeName);

            Route* route = routeBinarySearch(routeName);
            if (route) {
                busBinaryInsert(new Bus(vin, type, cap, pas, num, currStop, route));
            }
        }
    }

    file.close();
    std::cout << "Loaded successfully from " << filename << std::endl;
}

void startSimulation() {
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 100);

    std::unordered_map<Stop*, std::array<int, 2>> coords;

    std::cout << "Randomizing stop placements..." << std::endl;
    for (std::vector<Stop*>::const_iterator it = registeredStops.cbegin(); it < registeredStops.cend(); ++it) {
        int x = dist(rng);
        int y = dist(rng);
        coords.insert({ *it, { x, y }});
        std::cout << **it << " is located at (" << x << ", " << y << ")" << std::endl;
    }

    for (std::vector<Route*>::const_iterator it = registeredRoutes.cbegin(); it < registeredRoutes.cend(); ++it) { // XXX If one stop in route
        std::cout << "Calculating delays for " << **it << std::endl;

        StopNode* node = (*it)->getHead();
        do {
            StopNode* nextNode;
            if (node->getNextStopNode()) {
                nextNode = node->getNextStopNode();
            } else {
                nextNode = (*it)->getHead();
            }

            Stop* stop = node->getStop();
            Stop* newStop = nextNode->getStop();
            int x = coords.at(stop)[0] - coords.at(newStop)[0];
            int y = coords.at(stop)[1] - coords.at(newStop)[1];
            int dist = std::sqrt(x * x + y * y) / 10;
            node->setTimeToNextStop(dist);

            std::cout << "from " << stop->getStopName() << " to " << newStop->getStopName() << " has delay " << dist << std::endl;

            node = node->getNextStopNode();
        } while (node != nullptr);
    }

    std::cout << "Randomizing bus locations..." << std::endl;
    std::uniform_int_distribution<int> moves(0, 10);
    for (std::vector<Bus*>::iterator it = registeredBuses.begin(); it < registeredBuses.end(); ++it) {
        for (int i = 0; i < moves(rng); i++) {
            (*it)->move();
        }
        std::cout << **it << " is now at stop " << (*it)->getCurrentStop() << std::endl;
    }

    std::cout << "How many times steps would you like to run the simulation for:" << std::endl;
    int steps = getValidInt();

    int counter = 0;
    std::cout << "Starting simulation..." << std::endl;
    while (counter <= steps) { // Event loop
        std::cout << "Step " << counter << std::endl;
        for (std::vector<Bus*>::iterator it = registeredBuses.begin(); it < registeredBuses.end(); ++it) {
            (*it)->progress();
        }

        counter++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void beginPromptLoop() {


    std::cout << "\nTransitManager started!" << std::endl;

    for (int userAction = getUserAction(); userAction != QUIT; userAction = getUserAction()) {
        switch (userAction) {
            case PRINT_BUSES:
                std::cout << "Registered buses:" << std::endl;
                printVector(registeredBuses);
                break;
            case PRINT_ROUTES:
                std::cout << "Registered routes:" << std::endl;
                printVector(registeredRoutes);
                break;
            case PRINT_STOPS:
                std::cout << "Registered stops:" << std::endl;
                printVector(registeredStops);
                break;
            case PRINT_STOPS_IN_ROUTE:
                printRouteStops();
                break;
            case ADD_BUS:
                addBus();
                break;
            case ADD_ROUTE:
                addRoute();
                break;
            case ADD_STOP:
                addStop();
                break;
            case REMOVE_BUS:
                removeBus();
                break;
            case REMOVE_ROUTE:
                removeRoute();
                break;
            case REMOVE_STOP:
                removeStop();
                break;
            case ADD_ROUTE_STOP_BEGIN:
                prependStopToRoute();
                break;
            case ADD_ROUTE_STOP_END:
                appendStopToRoute();
                break;
            case ADD_ROUTE_STOP_BEFORE:
                addStopBeforeToRoute();
                break;
            case ADD_ROUTE_STOP_AFTER:
                addStopAfterToRoute();
                break;
            case REMOVE_ROUTE_STOP:
                removeStopFromRoute();
                break;
            case SAVE_REG: {
                std::cout << "Enter filename to save to:" << std::endl;
                saveRegistry(getNonEmptyString());
            }
            break;
            case LOAD_REG: {
                std::cout << "Enter filename to load from:" << std::endl;
                loadRegistry(getNonEmptyString());
            }
            break;

            case BEGIN_SIM:
                startSimulation();
                break;
            default:
                std::cout << "Unknown action!" << std::endl;
                break;
        }

        std::cout << std::endl;
    }

    deleteVector(registeredBuses);
    deleteVector(registeredRoutes);
    deleteVector(registeredStops);

    std::cout << "The transit manager has been quit! Goodbye!" << std::endl;
}

