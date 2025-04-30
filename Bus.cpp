//
// Created by haibi on 4/29/2025.
//

#include "Bus.h"

void Bus::move() override {

}

int Bus::getBusNumber() const {
    return this->busNumber;
}

int Bus::getCurrentStop() const {
    return this->currentStop;
}

Route Bus::getRoute() const {
    return this->route;
}