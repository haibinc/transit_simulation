//
// Created by haibi on 4/29/2025.
// Updated by Kunj on 5/2/2025.
// Updated by Daniel on 5/8/2025.
//

#ifndef STOP_H
#define STOP_H

#include <string>
#include <vector>
#include "Passenger.h"

class Stop
{
private:
    std::string stopName;
    std::vector<Passenger*> passengers; 
    Stop *nextStop;
    Stop *prevStop;
    int timeToNextStop;

public:
    Stop();
    Stop(const std::string &stopName, Stop *nextStop, Stop *prevStop, const int timeToNextStop) : stopName(stopName), nextStop(nextStop), prevStop(prevStop), timeToNextStop(timeToNextStop) {};

    Stop *getNextStop() const;
    Stop *getPrevStop() const;
    int getTimeToNextStop() const;
    const std::string &getStopName() const;
    std::vector<Passenger*> getPassengers() const;

    void setStopName(const std::string &name);
    void setNextStop(Stop *stop);
    void setPrevStop(Stop *stop);
    void setTimeToNextStop(int time);

    void addPassenger(Passenger* passenger);
    void removePassenger(Passenger* passenger);
};

#endif // STOP_H
