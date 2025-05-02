#include "Route.h"
#include <iostream>

Route::Route(const std::string &name) : routeName(name), head(nullptr), tail(nullptr), numStops(0) {}

Route::~Route() { clearRoute(); }

int Route::getNumStops() const { return numStops; }

void Route::addStopToFront(Stop *stop)
{
    if (!head)
    {
        head = tail = stop;
    }
    else
    {
        stop->setNextStop(head);
        head->setPrevStop(stop);
        head = stop;
    }
    ++numStops;
}

void Route::addStopToBack(Stop *stop)
{
    if (!tail)
    {
        head = tail = stop;
    }
    else
    {
        tail->setNextStop(stop);
        stop->setPrevStop(tail);
        tail = stop;
    }
    ++numStops;
}

void Route::addStopAfter(Stop *addStop, const std::string &existingStop)
{
    Stop *current = head;
    while (current && current->getStopName() != existingStop)
    {
        current = current->getNextStop();
    }
    if (current)
    {
        addStop->setNextStop(current->getNextStop());
        addStop->setPrevStop(current);
        if (current->getNextStop())
            current->getNextStop()->setPrevStop(addStop);
        current->setNextStop(addStop);
        if (current == tail)
            tail = addStop;
        ++numStops;
    }
}

void Route::removeStop(const std::string &name)
{
    Stop *current = head;
    while (current && current->getStopName() != name)
    {
        current = current->getNextStop();
    }
    if (current)
    {
        if (current->getPrevStop())
            current->getPrevStop()->setNextStop(current->getNextStop());
        if (current->getNextStop())
            current->getNextStop()->setPrevStop(current->getPrevStop());
        if (current == head)
            head = current->getNextStop();
        if (current == tail)
            tail = current->getPrevStop();
        delete current;
        --numStops;
    }
}

void Route::printRouteForward() const
{
    Stop *current = head;
    while (current)
    {
        std::cout << current->getStopName() << " -> ";
        current = current->getNextStop();
    }
    std::cout << "END\n";
}

void Route::printRouteBackward() const
{
    Stop *current = tail;
    while (current)
    {
        std::cout << current->getStopName() << " <- ";
        current = current->getPrevStop();
    }
    std::cout << "START\n";
}

const std::string &Route::getRouteName() const { return routeName; }

bool Route::stopExist(const std::string &name) const
{
    Stop *current = head;
    while (current)
    {
        if (current->getStopName() == name)
            return true;
        current = current->getNextStop();
    }
    return false;
}

void Route::clearRoute()
{
    while (head)
    {
        Stop *temp = head;
        head = head->getNextStop();
        delete temp;
    }
    tail = nullptr;
    numStops = 0;
}