//
// Created by haibi on 4/29/2025.
// Updated by Misha on 5/2/2025.
//

#ifndef ROUTE_H
#define ROUTE_H
#include "Stop.h"
#include "StopNode.h"
#include <ostream>


class Route {
private:
    std::string routeName;
    StopNode* head;
    StopNode* tail;
    int numStops;
public:
    Route(const std::string& name);
    ~Route();

    int getNumStops() const;
    void addStopToFront(Stop* stop);
    void addStopToBack(Stop* stop);
    void addStopBefore(Stop* addStop, const std::string& existingStop);
    void addStopAfter(Stop* addStop, const std::string& existingStop);
    void removeStop(const std::string& name);
    void printRouteForward() const;
    void printRouteBackward() const;
    const std::string& getRouteName() const;
    bool stopExist(const std::string& name) const;
    Stop* getStop(const std::string& name) const;
    void clearRoute();
};

std::ostream& operator<<(std::ostream& strm, const Route& route);

bool operator<(const Route& lhs, const Route& rhs);

bool operator>(const Route& lhs, const Route& rhs);

bool operator==(const Route& lhs, const Route& rhs);

bool operator==(const std::string& lhs, Route& rhs);

bool operator==(const Route& lhs, const std::string& rhs);

bool operator<(const std::string& lhs, const Route& rhs);

bool operator<(const Route& lhs, const std::string& rhs);

bool operator>(const std::string& lhs, const Route& rhs);

bool operator>(const Route& lhs, const std::string& rhs);



#endif //ROUTE_H
