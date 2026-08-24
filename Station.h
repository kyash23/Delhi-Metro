#ifndef STATION_H
#define STATION_H

#include <string>
#include <vector>
using namespace std;

/*
 * ============================================================
 *  CLASS: Station
 * ============================================================
 *  Think of this like a real metro station.
 *  Every station has:
 *    - A name          (e.g., "Rajiv Chowk")
 *    - Line(s) it's on (e.g., "Yellow", "Blue")
 *    - Whether it's an interchange (connects 2+ lines)
 * ============================================================
 */
class Station {
private:
    // --- Data stored inside each station ---
    string name;                // Name of the station
    vector<string> lines;       // Which metro lines pass through here
    bool isInterchangeStation;  // true if 2+ lines meet here

public:
    // --- Constructors ---
    Station();                              // Empty station
    Station(string stationName, string lineName);  // Station on one line

    // --- Simple getters (read data) ---
    string getName();
    vector<string> getLines();
    bool isInterchange();

    // --- Add another line to this station ---
    void addLine(string lineName);

    // --- Check if two stations are the same ---
    bool operator==(Station other);

    // --- Print station info as a string ---
    string toString();
};

#endif
