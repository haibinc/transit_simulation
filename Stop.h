//
// Created by haibi on 4/29/2025.
// Updated by Kunj on 5/2/2025.
// Updated by Daniel on 5/8/2025.
//

#ifndef STOP_H
#define STOP_H

#include <string>
#include <vector>
#include <ostream>
#include "Passenger.h"

class Stop
{
private:
    std::string stopName;
    std::vector<Passenger*> passengers; 

public:
    Stop();
    Stop(const std::string &stopName) : stopName(stopName) {};

    const std::string &getStopName() const;
    std::vector<Passenger*> getPassengers() const;

    void setStopName(const std::string &name);
    void addPassenger(Passenger* passenger);
    void removePassenger(Passenger* passenger);
};

std::ostream& operator<<(std::ostream& strm, const Stop& stop);

bool operator<(const Stop& lhs, const Stop& rhs);

bool operator>(const Stop& lhs, const Stop& rhs);

bool operator==(const Stop& lhs, const Stop& rhs);

bool operator==(const std::string& lhs, Stop& rhs);

bool operator==(const Stop& lhs, const std::string& rhs);

bool operator<(const std::string& lhs, const Stop& rhs);

bool operator<(const Stop& lhs, const std::string& rhs);

bool operator>(const std::string& lhs, const Stop& rhs);

bool operator>(const Stop& lhs, const std::string& rhs);

#endif // STOP_H
