//
// Updated by Kunj on 5/2/2025
//
#include <iostream>
#include "Route.h"
#include "Stop.h"
#include "Bus.h"
#include "TransitManager.h"

int main()
{
    // // Create Route and Stops
    // Route route("City Loop");

    // Stop *central = new Stop("Central Station");
    // Stop *park = new Stop("Park Avenue");
    // Stop *downtown = new Stop("Downtown");
    // Stop *uptown = new Stop("Uptown");

    // route.addStopToBack(central);
    // route.addStopToBack(park);
    // route.addStopToBack(downtown);
    // route.addStopToBack(uptown);

    // // Display the route
    // std::cout << "Route forward:\n";
    // route.printRouteForward();

    // std::cout << "Route backward:\n";
    // route.printRouteBackward();

    // // Create Bus and simulate movement
    // Bus bus("VIN12345", "City Bus", 40, 10, 25, 0, &route);

    // std::cout << "\nSimulating Bus Movement:\n";
    // for (int i = 0; i < route.getNumStops() + 2; ++i)
    // {
    //     bus.move();
    // }

    beginPromptLoop();

    // // Cleanup dynamically allocated memory
    // route.clearRoute();

    return 0;
}