//
// Created by haibi on 4/29/2025.
//

#include "Route.h"
#include <iostream>

Route::Route(const std::string &name) {
    this->routeName = name;
}

int Route::getNumStops() const{
    return this->numStops;
}

bool Route::stopExist(const std::string &name) const{
    Stop *currentStop = this->head;
    while (currentStop != nullptr) {
        if (currentStop->getStopName() == name) {
            return true;
        }
        currentStop = currentStop->getNextStop();
    }
    return false;
}

void Route::addStopToFront(Stop *stop) {
    if (head == nullptr) {
        head = tail = stop;
    } else {
        stop->setNextStop(head);
        stop->setPrevStop(nullptr);
        head->setPrevStop(stop);
        head = stop;
    }
    this->numStops += 1;
}

void Route::addStopToBack(Stop *stop) {
    if (head == nullptr) {
        head = tail = stop;
    } else {
        tail->setNextStop(stop);
        stop->setPrevStop(tail);
        stop->setNextStop(nullptr);
        tail = stop;
    }
    this->numStops += 1;
}

void Route::addStopAfter(Stop *addStop, const std::string &existingStop) {
    Stop *currentStop = this->head;

    while (currentStop != nullptr && currentStop->getStopName() != existingStop) {
        currentStop = currentStop->getNextStop();
    }
    if (currentStop != nullptr) {
        addStop->setNextStop(currentStop->getNextStop());
        addStop->setPrevStop(currentStop);
        currentStop->setNextStop(addStop);
        this->numStops += 1;
    }
}

void Route::removeStop(const std::string &name) {
    Stop *currentStop = this->head;

    while (currentStop != nullptr) {
        if (currentStop->getStopName() == name) {
            Stop *prev = currentStop->getPrevStop();
            Stop *next = currentStop->getNextStop();

            if (prev) {
                prev->setNextStop(next);
            } else {
                head = next;
            }
            if (next) {
                next->setPrevStop(prev);
            } else {
                tail = prev;
            }

            delete currentStop;
            numStops -= 1;
            return;
        }
        currentStop = currentStop->getNextStop();
    }
}

void Route::printRouteForward() const {
    Stop* currentStop = head;
    int i = 1;
    while (currentStop != nullptr) {
        std::cout << "Stop " << i << ": " << currentStop->getStopName() << std::endl;
        currentStop = currentStop->getNextStop();
    }
}

void Route::printRouteBackward() const {
    Stop* currentStop = tail;
    int i = this->numStops;
    while (currentStop != nullptr) {
        std::cout << "Stop " << i << ": " << currentStop->getStopName() << std::endl;
        currentStop = currentStop->getPrevStop();
    }
}

const std::string& Route::getRouteName() const {
    return this->routeName;
}

void Route::clearRoute() {
    Stop* currentStop = head;

    while (currentStop != nullptr) {
        Stop* next = currentStop->getNextStop();
        delete currentStop;
        currentStop = next;
    }
    head = nullptr;
    tail = nullptr;
    numStops = 0;
}

Route::~Route() {
    clearRoute();
}
