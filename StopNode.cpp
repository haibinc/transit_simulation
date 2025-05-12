/*
Made by Misha
*/

#include "StopNode.h"

StopNode::StopNode(Stop* stop, int timeToNext) {
    data = stop;
    nextStop = nullptr;
    prevStop = nullptr;
    timeToNextStop = timeToNext;
}

StopNode *StopNode::getNextStopNode() const { return nextStop; }

StopNode *StopNode::getPrevStopNode() const { return prevStop; }

int StopNode::getTimeToNextStop() const { return timeToNextStop; }

Stop* StopNode::getStop() const { return data; }

void StopNode::setNextStopNode(StopNode* stop) { nextStop = stop; }

void StopNode::setPrevStopNode(StopNode* stop) { prevStop = stop; }

void StopNode::setTimeToNextStop(int time) { timeToNextStop = time; }

void StopNode::setStop(Stop* stop) { data = stop; }