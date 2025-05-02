//
// Created by Habin on 4/29/2025.
// Updated by Kunj on 5/2/2025.
//

#include "Stop.h"

Stop::Stop() : stopName(""), nextStop(nullptr), prevStop(nullptr), timeToNextStop(0) {}

Stop *Stop::getNextStop() const { return nextStop; }

Stop *Stop::getPrevStop() const { return prevStop; }

int Stop::getTimeToNextStop() const { return timeToNextStop; }

const std::string &Stop::getStopName() const { return stopName; }

void Stop::setStopName(const std::string &name) { stopName = name; }

void Stop::setNextStop(Stop *stop) { nextStop = stop; }

void Stop::setPrevStop(Stop *stop) { prevStop = stop; }

void Stop::setTimeToNextStop(int time) { timeToNextStop = time; }