/*
Made by Misha
*/

#ifndef STOPNODE_H
#define STOPNODE_H

#include "Stop.h"

class StopNode {
    private:
        Stop* data;
        StopNode* nextStop;
        StopNode* prevStop;
        int timeToNextStop;

    public:
        StopNode(Stop* stop, int timeToNext = 0);

        StopNode *getNextStopNode() const;
        StopNode *getPrevStopNode() const;
        int getTimeToNextStop() const;
        Stop* getStop() const;
        
        void setNextStopNode(StopNode *stop);
        void setPrevStopNode(StopNode *stop);
        void setTimeToNextStop(int time);
        void setStop(Stop* stop);
};

#endif