#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include "Graph.h"
#include <vector>
#include <string>
using namespace std;

/*
 * ============================================================
 *  STRUCT: RouteResult
 * ============================================================
 *  Stores everything about a route we found:
 *    - The path (list of station names)
 *    - Total distance, time, stops
 *    - Fare (ticket price)
 *    - Where you need to change lines (interchanges)
 *    - Which algorithm found this route
 * ============================================================
 */
struct RouteResult {
    vector<string> path;           // List of stations from start to end
    double totalDistance;           // Total distance in km
    int totalTime;                 // Total time in minutes
    int totalStops;                // Number of stops
    double fare;                   // Ticket price in rupees
    vector<string> interchanges;   // Stations where you change lines
    string algorithm;              // Which algorithm found this
    bool found;                    // Did we find a route?

    // Default constructor
    RouteResult() {
        totalDistance = 0;
        totalTime = 0;
        totalStops = 0;
        fare = 0;
        found = false;
    }
};

/*
 * ============================================================
 *  CLASS: RoutePlanner
 * ============================================================
 *  This is where the MAGIC happens!
 *  Contains 3 algorithms to find routes:
 *
 *  1. DIJKSTRA  = Finds SHORTEST DISTANCE path
 *                 Uses: Min-Heap (priority queue)
 *                 Speed: O((V+E) log V)
 *
 *  2. BFS       = Finds path with FEWEST STOPS
 *                 Uses: Queue (FIFO - first in, first out)
 *                 Speed: O(V + E)
 *
 *  3. DFS       = Finds ANY path (explores deeply)
 *                 Uses: Stack (LIFO - last in, first out)
 *                 Speed: O(V + E)
 *                 WARNING: Does NOT guarantee shortest path!
 * ============================================================
 */
class RoutePlanner {
private:
    Graph graph;  // The metro network we're planning routes on

    // Helper functions
    double calculateFare(double distance);
    vector<string> detectInterchanges(vector<string> path);
    double calculatePathDistance(vector<string> path);
    int calculatePathTime(vector<string> path);
    RouteResult buildResult(vector<string> path, string algoName);

public:
    RoutePlanner(Graph g);

    // The 3 main algorithms
    RouteResult dijkstra(string source, string destination);
    RouteResult bfs(string source, string destination);
    RouteResult dfs(string source, string destination);

    // Display results
    void displayRoute(RouteResult result);
    void compareRoutes(string source, string destination);
};

#endif
