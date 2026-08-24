/*
 * ============================================================
 *  test_routes.cpp  —  Unit Tests
 * ============================================================
 *  This file tests that all our code works correctly.
 *
 *  Build & Run:
 *    g++ -std=c++14 -I include src/Station.cpp src/Graph.cpp src/RoutePlanner.cpp tests/test_routes.cpp -o test_metro.exe
 *    ./test_metro.exe
 * ============================================================
 */

#include <iostream>
#include <cassert>   // assert() = crash if condition is false
#include <cmath>     // for abs()
#include "Station.h"
#include "Graph.h"
#include "RoutePlanner.h"
using namespace std;

int testsRun = 0;
int testsPassed = 0;

// ============================================================
// Helper: Build a small test graph for testing
// ============================================================
//
//   A ---2km--- B ---3km--- C ---1.5km--- D ---4km--- E
//   |                                                   |
//   +------------------15km----------------------------+
//
// The short path A→E = A→B→C→D→E = 10.5 km
// The direct path A→E = 15 km (longer!)
//
// Dijkstra should pick the 10.5 km path.
// BFS should pick the 1-stop direct path (A→E).
// This proves they optimize for DIFFERENT things!
//
Graph buildTestGraph() {
    Graph g;

    // Add stations (C is on both Yellow and Blue = interchange)
    g.addStation(Station("A", "Yellow"));
    g.addStation(Station("B", "Yellow"));
    g.addStation(Station("C", "Yellow"));
    g.addStation(Station("C", "Blue"));   // C becomes interchange!
    g.addStation(Station("D", "Blue"));
    g.addStation(Station("E", "Blue"));

    // Add connections
    g.addEdge("A", "B", 2.0, 3);     // A -- B: 2 km
    g.addEdge("B", "C", 3.0, 4);     // B -- C: 3 km
    g.addEdge("C", "D", 1.5, 2);     // C -- D: 1.5 km
    g.addEdge("D", "E", 4.0, 6);     // D -- E: 4 km
    g.addEdge("A", "E", 15.0, 20);   // A -- E: 15 km (direct but long!)

    return g;
}


// ============================================================
// TEST 1: Can we create a station correctly?
// ============================================================
void testStationCreation() {
    cout << "  [TEST] Station Creation... ";
    testsRun++;

    Station s("Rajiv Chowk", "Yellow");

    // Check name
    assert(s.getName() == "Rajiv Chowk");

    // Check it has 1 line
    assert(s.getLines().size() == 1);
    assert(s.getLines()[0] == "Yellow");

    // Not an interchange yet
    assert(s.isInterchange() == false);

    // Now add Blue line — should become interchange
    s.addLine("Blue");
    assert(s.getLines().size() == 2);
    assert(s.isInterchange() == true);

    cout << "PASSED" << endl;
    testsPassed++;
}


// ============================================================
// TEST 2: Can we build a graph correctly?
// ============================================================
void testGraphConstruction() {
    cout << "  [TEST] Graph Construction... ";
    testsRun++;

    Graph g = buildTestGraph();

    // Should have 5 unique stations
    assert(g.getStationCount() == 5);

    // Should have 5 edges
    assert(g.getEdgeCount() == 5);

    // Stations should exist
    assert(g.hasStation("A") == true);
    assert(g.hasStation("E") == true);
    assert(g.hasStation("Z") == false);  // Z doesn't exist

    // C should be an interchange (Yellow + Blue)
    assert(g.getStation("C").isInterchange() == true);
    assert(g.getStation("C").getLines().size() == 2);

    cout << "PASSED" << endl;
    testsPassed++;
}


// ============================================================
// TEST 3: Does adjacency list store neighbors correctly?
// ============================================================
void testAdjacencyList() {
    cout << "  [TEST] Adjacency List Neighbors... ";
    testsRun++;

    Graph g = buildTestGraph();

    // C should be connected to B and D
    vector<Edge> neighbors = g.getNeighbors("C");
    assert(neighbors.size() == 2);

    bool hasB = false;
    bool hasD = false;
    for (int i = 0; i < neighbors.size(); i++) {
        if (neighbors[i].destination == "B") hasB = true;
        if (neighbors[i].destination == "D") hasD = true;
    }
    assert(hasB == true);
    assert(hasD == true);

    cout << "PASSED" << endl;
    testsPassed++;
}


// ============================================================
// TEST 4: Does Dijkstra find the shortest path?
// ============================================================
void testDijkstraShortestPath() {
    cout << "  [TEST] Dijkstra Shortest Path... ";
    testsRun++;

    Graph g = buildTestGraph();
    RoutePlanner planner(g);

    RouteResult result = planner.dijkstra("A", "E");
    assert(result.found == true);

    // Shortest path: A→B→C→D→E = 2+3+1.5+4 = 10.5 km
    // NOT the direct path A→E = 15 km
    assert(result.path.size() == 5);           // 5 stations
    assert(result.path[0] == "A");             // Starts at A
    assert(result.path[4] == "E");             // Ends at E
    assert(abs(result.totalDistance - 10.5) < 0.01);  // Distance = 10.5 km

    cout << "PASSED" << endl;
    testsPassed++;
}


// ============================================================
// TEST 5: Does BFS find the path with fewest stops?
// ============================================================
void testBFSMinimumStops() {
    cout << "  [TEST] BFS Minimum Stops... ";
    testsRun++;

    Graph g = buildTestGraph();
    RoutePlanner planner(g);

    RouteResult result = planner.bfs("A", "E");
    assert(result.found == true);

    // BFS should find A→E direct (1 stop) since it exists
    // Even though it's 15 km, BFS doesn't care about distance!
    assert(result.totalStops == 1);
    assert(result.path.size() == 2);  // Just A and E
    assert(result.path[0] == "A");
    assert(result.path[1] == "E");

    cout << "PASSED" << endl;
    testsPassed++;
}


// ============================================================
// TEST 6: Does DFS find SOME valid path?
// ============================================================
void testDFSFindsPath() {
    cout << "  [TEST] DFS Finds A Path... ";
    testsRun++;

    Graph g = buildTestGraph();
    RoutePlanner planner(g);

    RouteResult result = planner.dfs("A", "E");
    assert(result.found == true);

    // DFS should find SOME path (not necessarily optimal)
    assert(result.path.front() == "A");
    assert(result.path.back() == "E");
    assert(result.path.size() >= 2);

    cout << "PASSED" << endl;
    testsPassed++;
}


// ============================================================
// TEST 7: Is fare calculated correctly?
// ============================================================
void testFareCalculation() {
    cout << "  [TEST] Fare Calculation... ";
    testsRun++;

    Graph g = buildTestGraph();
    RoutePlanner planner(g);

    // A→B = 2.0 km → fare should be Rs 10 (0-2 km slab)
    RouteResult r1 = planner.dijkstra("A", "B");
    assert(r1.found == true);
    assert(r1.fare == 10.0);

    // A→B→C = 5.0 km → fare should be Rs 20 (2-5 km slab)
    RouteResult r2 = planner.dijkstra("A", "C");
    assert(r2.found == true);
    assert(r2.fare == 20.0);

    cout << "PASSED" << endl;
    testsPassed++;
}


// ============================================================
// TEST 8: Are interchange stations detected?
// ============================================================
void testInterchangeDetection() {
    cout << "  [TEST] Interchange Detection... ";
    testsRun++;

    Graph g = buildTestGraph();
    RoutePlanner planner(g);

    // Path A(Yellow)→B(Yellow)→C(Yellow/Blue)→D(Blue)→E(Blue)
    // C should be detected as interchange
    RouteResult result = planner.dijkstra("A", "E");
    assert(result.found == true);

    bool foundC = false;
    for (int i = 0; i < result.interchanges.size(); i++) {
        if (result.interchanges[i] == "C") foundC = true;
    }
    assert(foundC == true);

    cout << "PASSED" << endl;
    testsPassed++;
}


// ============================================================
// TEST 9: Same source and destination
// ============================================================
void testSameSourceDest() {
    cout << "  [TEST] Same Source and Destination... ";
    testsRun++;

    Graph g = buildTestGraph();
    RoutePlanner planner(g);

    RouteResult result = planner.dijkstra("A", "A");
    assert(result.found == true);
    assert(result.totalStops == 0);
    assert(result.totalDistance == 0.0);

    cout << "PASSED" << endl;
    testsPassed++;
}


// ============================================================
// TEST 10: Station that doesn't exist
// ============================================================
void testNonExistentStation() {
    cout << "  [TEST] Non-Existent Station... ";
    testsRun++;

    Graph g = buildTestGraph();
    RoutePlanner planner(g);

    RouteResult r1 = planner.dijkstra("A", "Z");
    assert(r1.found == false);

    RouteResult r2 = planner.bfs("Z", "A");
    assert(r2.found == false);

    cout << "PASSED" << endl;
    testsPassed++;
}


// ============================================================
// TEST 11: Multi-line route through interchange
// ============================================================
void testMultiLineRoute() {
    cout << "  [TEST] Multi-Line Route (Integration)... ";
    testsRun++;

    // Build a mini Delhi Metro for testing
    Graph g;
    g.addStation(Station("Samaypur Badli", "Yellow"));
    g.addStation(Station("Rajiv Chowk", "Yellow"));
    g.addStation(Station("Rajiv Chowk", "Blue"));
    g.addStation(Station("Dwarka", "Blue"));

    g.addEdge("Samaypur Badli", "Rajiv Chowk", 15.0, 20);
    g.addEdge("Rajiv Chowk", "Dwarka", 14.0, 22);

    RoutePlanner planner(g);

    // Route from Yellow line to Blue line
    RouteResult result = planner.dijkstra("Samaypur Badli", "Dwarka");
    assert(result.found == true);

    // Must go through Rajiv Chowk (the interchange)
    bool throughRC = false;
    for (int i = 0; i < result.path.size(); i++) {
        if (result.path[i] == "Rajiv Chowk") throughRC = true;
    }
    assert(throughRC == true);

    cout << "PASSED" << endl;
    testsPassed++;
}


// ============================================================
// TEST 12: Dijkstra vs BFS give different optimal results
// ============================================================
void testDijkstraVsBFS() {
    cout << "  [TEST] Dijkstra vs BFS (Different Goals)... ";
    testsRun++;

    Graph g = buildTestGraph();
    RoutePlanner planner(g);

    RouteResult dijResult = planner.dijkstra("A", "E");
    RouteResult bfsResult = planner.bfs("A", "E");

    // Dijkstra: A→B→C→D→E (4 stops, 10.5 km) — optimizes DISTANCE
    // BFS:      A→E        (1 stop,  15.0 km) — optimizes STOPS

    // Dijkstra should have shorter distance
    assert(dijResult.totalDistance <= bfsResult.totalDistance);

    // BFS should have fewer stops
    assert(bfsResult.totalStops <= dijResult.totalStops);

    cout << "PASSED" << endl;
    testsPassed++;
}


// ============================================================
// MAIN — Run all tests
// ============================================================
int main() {
    cout << endl;
    cout << "  ========================================" << endl;
    cout << "   Metro Navigation System - Unit Tests" << endl;
    cout << "  ========================================" << endl;
    cout << endl;

    testStationCreation();
    testGraphConstruction();
    testAdjacencyList();
    testDijkstraShortestPath();
    testBFSMinimumStops();
    testDFSFindsPath();
    testFareCalculation();
    testInterchangeDetection();
    testSameSourceDest();
    testNonExistentStation();
    testMultiLineRoute();
    testDijkstraVsBFS();

    cout << endl;
    cout << "  ========================================" << endl;
    cout << "   Results: " << testsPassed << "/" << testsRun
         << " tests passed" << endl;
    cout << "  ========================================" << endl;
    cout << endl;

    if (testsPassed == testsRun) {
        return 0;  // All tests passed!
    } else {
        return 1;  // Some tests failed
    }
}
