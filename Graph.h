#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>
#include "Station.h"
using namespace std;

/*
 * ============================================================
 *  STRUCT: Edge
 * ============================================================
 *  An edge = a track between two stations.
 *  It stores:
 *    - Where the track goes (destination station name)
 *    - How far it is (distance in km)
 *    - How long it takes (time in minutes)
 *
 *  Example: Edge from "Rajiv Chowk" to "New Delhi" = 1.1 km, 2 min
 * ============================================================
 */
struct Edge {
    string destination;  // Name of the station this track goes to
    double distance;     // Distance in kilometers
    int time;            // Time in minutes

    // Constructor to create an edge
    Edge(string dest, double dist, int t) {
        destination = dest;
        distance = dist;
        time = t;
    }
};

/*
 * ============================================================
 *  CLASS: Graph
 * ============================================================
 *  The metro network is stored as a GRAPH.
 *
 *  What is a Graph?
 *    - A collection of NODES (stations) connected by EDGES (tracks)
 *    - Each edge has a WEIGHT (distance/time)
 *
 *  We use an ADJACENCY LIST to store the graph:
 *    - It's like a dictionary/map
 *    - Key   = station name
 *    - Value = list of edges (connections to other stations)
 *
 *  Example:
 *    "Rajiv Chowk" --> [("New Delhi", 1.1km), ("Patel Chowk", 0.9km),
 *                       ("Karol Bagh", 2.8km), ("Barakhamba Road", 0.8km)]
 *
 *  Why Adjacency List (not Adjacency Matrix)?
 *    - Metro is a SPARSE graph (each station connects to only 2-3 others)
 *    - Adjacency List uses O(V + E) memory  <-- efficient!
 *    - Adjacency Matrix uses O(V^2) memory  <-- wasteful for sparse graphs
 * ============================================================
 */
class Graph {
private:
    // THE ADJACENCY LIST:
    // Key = station name, Value = list of edges from that station
    map<string, vector<Edge>> adjList;

    // Station info storage:
    // Key = station name, Value = Station object with line info
    map<string, Station> stations;

    // Count of total edges (connections) in the graph
    int edgeCount;

public:
    Graph();

    // --- Building the graph ---
    void addStation(Station station);
    void addEdge(string from, string to, double distance, int time);

    // --- Looking up information ---
    bool hasStation(string name);
    Station getStation(string name);
    vector<Edge> getNeighbors(string stationName);
    vector<string> getAllStationNames();
    vector<string> getStationsByLine(string lineName);

    // --- Statistics ---
    int getStationCount();
    int getEdgeCount();

    // --- Display ---
    void displayGraph();
};

#endif
