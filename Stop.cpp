//
// Created by haibi on 4/29/2025.
//

#include "Stop.h"

Stop::Stop() {
    this->nextStop = nullptr;
    this->prevStop = nullptr;
    this->stopName = "Main Street";
    this->timeToNextStop = 0;
}

Stop* Stop::getNextStop() const {
    return this->nextStop;
}

Stop* Stop::getPrevStop() const {
    return this->prevStop;
}

int Stop::getTimeToNextStop() const {
    return this->timeToNextStop;
}

const std::string& Stop::getStopName() const{
    return this->stopName;
}

void Stop::setStopName(const std::string& name) {
    this->stopName = name;
}
void Stop::setNextStop(Stop* stop) {
    this->nextStop = stop;
}

void Stop::setPrevStop(Stop* stop) {
    this->prevStop = stop;
}

void Stop::setTimeToNextStop(int time) {
    this->timeToNextStop = time;
}