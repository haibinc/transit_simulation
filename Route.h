//
// Created by haibi on 4/29/2025.
//

#ifndef ROUTE_H
#define ROUTE_H
#include "Stop.h"


class Route {
private:
    std::string routeName;
    Stop* head;
    Stop* tail;
    int numStops;
public:
    Route(const std::string& name);
    ~Route();

    int getNumStops() const;
    void addStopToFront(Stop* stop);
    void addStopToBack(Stop* stop);
    void addStopAfter(Stop* addStop, const std::string& existingStop);
    void removeStop(const std::string& name);
    void printRouteForward() const;
    void printRouteBackward() const;
    const std::string& getRouteName() const;
    bool stopExist(const std::string& name) const;
    void clearRoute();

};



#endif //ROUTE_H
