#ifndef METRO_SYSTEM_H
#define METRO_SYSTEM_H

#include "Graph.h"
#include "RoutePlanner.h"
#include <string>
using namespace std;

/*
 * ============================================================
 *  CLASS: MetroSystem
 * ============================================================
 *  This is the MAIN CLASS that ties everything together.
 *
 *  It has:
 *    - A Graph (the metro network)
 *    - A RoutePlanner (the algorithms)
 *    - An interactive menu for the user
 *
 *  OOP Concept: COMPOSITION
 *    MetroSystem "HAS A" Graph and "HAS A" RoutePlanner
 *    (instead of inheriting from them)
 * ============================================================
 */
class MetroSystem {
private:
    Graph graph;              // The metro network
    RoutePlanner* planner;    // Pointer to the route planner

    // Setup
    void loadMetroData();     // Load all station & connection data

    // Menu options
    void displayBanner();
    void displayMenu();
    void listAllStations();
    void displayMetroMap();
    void findShortestRoute();
    void findMinimumStops();
    void exploreRoute();
    void compareAllRoutes();
    void displayNetworkStats();

    // Helper
    string getStationInput(string prompt);

public:
    MetroSystem();   // Constructor: loads data & creates planner
    ~MetroSystem();  // Destructor: cleans up planner

    void run();      // Start the interactive menu
};

#endif
