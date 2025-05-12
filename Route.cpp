#include "Route.h"
#include "StopNode.h"
#include <iostream>
#include <ostream>

Route::Route(const std::string &name) : routeName(name), head(nullptr), tail(nullptr), numStops(0) {}

Route::~Route() { clearRoute(); }

int Route::getNumStops() const { return numStops; }

void Route::addStopToFront(Stop *stop)
{
    StopNode* newStop = new StopNode(stop);
    if (!head)
    {
        head = tail = newStop;
    }
    else
    {
        newStop->setNextStopNode(head);
        head->setPrevStopNode(newStop);
        head = newStop;
    }
    ++numStops;
}

void Route::addStopToBack(Stop *stop)
{
    StopNode* newStop = new StopNode(stop);
    if (!tail)
    {
        head = tail = newStop;
    }
    else
    {
        tail->setNextStopNode(newStop);
        newStop->setPrevStopNode(tail);
        tail = newStop;
    }
    ++numStops;
}

void Route::addStopBefore(Stop *addStop, const std::string &existingStop)
{
    StopNode *current = head;
    while (current && current->getStop()->getStopName() != existingStop)
    {
        current = current->getNextStopNode();
    }
    if (current)
    {
        StopNode* newStop = new StopNode(addStop);
        newStop->setNextStopNode(current);
        newStop->setPrevStopNode(current->getPrevStopNode());
        if (current->getPrevStopNode())
            current->getPrevStopNode()->setNextStopNode(newStop);
        current->setPrevStopNode(newStop);
        if (current == head)
            head = newStop;
        ++numStops;
    }
}

void Route::addStopAfter(Stop *addStop, const std::string &existingStop)
{
    StopNode *current = head;
    while (current && current->getStop()->getStopName() != existingStop)
    {
        current = current->getNextStopNode();
    }
    if (current)
    {
        StopNode* newStop = new StopNode(addStop);
        newStop->setNextStopNode(current->getNextStopNode());
        newStop->setPrevStopNode(current);
        if (current->getNextStopNode())
            current->getNextStopNode()->setPrevStopNode(newStop);
        current->setNextStopNode(newStop);
        if (current == tail)
            tail = newStop;
        ++numStops;
    }
}

void Route::removeStop(const std::string &name)
{
    StopNode *current = head;
    while (current && current->getStop()->getStopName() != name)
    {
        current = current->getNextStopNode();
    }
    if (current)
    {
        if (current->getPrevStopNode())
            current->getPrevStopNode()->setNextStopNode(current->getNextStopNode());
        if (current->getNextStopNode())
            current->getNextStopNode()->setPrevStopNode(current->getPrevStopNode());
        if (current == head)
            head = current->getNextStopNode();
        if (current == tail)
            tail = current->getPrevStopNode();
        delete current;
        --numStops;
    }
}

void Route::printRouteForward() const
{
    StopNode *current = head;
    while (current)
    {
        std::cout << current->getStop()->getStopName() << " -> ";
        current = current->getNextStopNode();
    }
    std::cout << "END\n";
}

void Route::printRouteBackward() const
{
    StopNode *current = tail;
    while (current)
    {
        std::cout << current->getStop()->getStopName() << " <- ";
        current = current->getPrevStopNode();
    }
    std::cout << "START\n";
}

const std::string &Route::getRouteName() const { return routeName; }

bool Route::stopExist(const std::string &name) const
{
    StopNode *current = head;
    while (current)
    {
        if (current->getStop()->getStopName() == name)
            return true;
        current = current->getNextStopNode();
    }
    return false;
}

Stop* Route::getStop(const std::string& name) const
{
    StopNode *current = head;
    while (current)
    {
        if (current->getStop()->getStopName() == name)
            return current->getStop();
        current = current->getNextStopNode();
    }
    return nullptr;
}

void Route::clearRoute()
{
    while (head)
    {
        StopNode *temp = head;
        head = head->getNextStopNode();
        delete temp;
    }
    tail = nullptr;
    numStops = 0;
}

StopNode* Route::getHead() {
    return head;
}

StopNode* Route::getTail() {
    return tail;
}

std::ostream& operator<<(std::ostream& strm, const Route& route) {
    strm << "Route(NAME:" << route.getRouteName() << ", SIZE:" << route.getNumStops() << ")";
    return strm;
}

bool operator<(const Route& lhs, const Route& rhs) {
    return lhs.getRouteName() < rhs.getRouteName();
}

bool operator>(const Route& lhs, const Route& rhs) {
    return rhs.getRouteName() > lhs.getRouteName();
}

bool operator==(const Route& lhs, const Route& rhs) {
    return lhs.getRouteName() == rhs.getRouteName();
}

bool operator==(const std::string& lhs, Route& rhs) {
    return lhs == rhs.getRouteName();
}

bool operator==(const Route& lhs, const std::string& rhs) {
    return lhs.getRouteName() == rhs;
}

bool operator<(const std::string& lhs, const Route& rhs) {
    return lhs < rhs.getRouteName();
}

bool operator<(const Route& lhs, const std::string& rhs) {
    return lhs.getRouteName() < rhs;
}

bool operator>(const std::string& lhs, const Route& rhs) {
    return lhs > rhs.getRouteName();
}

bool operator>(const Route& lhs, const std::string& rhs) {
    return lhs.getRouteName() > rhs;
}