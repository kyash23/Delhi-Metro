# 🚇 Delhi Metro Navigation System

A graph-based metro route planner built in **C++** using Object-Oriented Programming (OOP) principles. Implements **Dijkstra's Algorithm**, **BFS**, and **DFS** for efficient routing across a realistic Delhi Metro network.

## 📋 Features

| Feature | Description |
|---|---|
| **Shortest Route** | Dijkstra's algorithm finds the minimum-distance path |
| **Minimum Stops** | BFS finds the path with fewest stations |
| **Path Exploration** | DFS explores depth-first (demonstrates non-optimal traversal) |
| **Algorithm Comparison** | Side-by-side comparison of all three algorithms |
| **Fare Calculator** | Distance-based fare slabs (Delhi Metro pricing) |
| **Interchange Detection** | Automatically detects line changes along the route |
| **Fuzzy Search** | Case-insensitive station input with suggestions |
| **Network Stats** | Displays graph properties (V, E, complexity) |
| **Adjacency List View** | Visualize the raw graph data structure |

## 🏗️ Project Structure

```
MetroApp/
├── include/               # Header files (class declarations)
│   ├── Station.h          # Station class (name, lines, interchange)
│   ├── Graph.h            # Graph class (adjacency list)
│   ├── RoutePlanner.h     # Algorithm implementations
│   └── MetroSystem.h      # Main controller class
├── src/                   # Source files (implementations)
│   ├── Station.cpp
│   ├── Graph.cpp
│   ├── RoutePlanner.cpp
│   ├── MetroSystem.cpp
│   └── main.cpp           # Entry point
├── tests/
│   └── test_routes.cpp    # 12 unit tests
├── CMakeLists.txt         # CMake build config
└── README.md
```

## 🚀 Build & Run

### Using g++ directly:
```bash
# Compile the main application
g++ -std=c++14 -I include src/*.cpp -o metro_app.exe

# Run it
./metro_app.exe

# Compile and run tests
g++ -std=c++14 -I include src/Station.cpp src/Graph.cpp src/RoutePlanner.cpp tests/test_routes.cpp -o test_metro.exe
./test_metro.exe
```

### Using CMake:
```bash
mkdir build && cd build
cmake ..
cmake --build .
./metro_app
./test_metro
```

## 🧠 Algorithms

### 1. Dijkstra's Algorithm (Shortest Distance)
- **Data Structure**: Min-Heap (priority_queue)
- **Time Complexity**: O((V + E) log V)
- **Guarantee**: Optimal shortest weighted path

### 2. Breadth-First Search (Minimum Stops)
- **Data Structure**: Queue (FIFO)
- **Time Complexity**: O(V + E)
- **Guarantee**: Optimal minimum-hop path

### 3. Depth-First Search (Exploration)
- **Data Structure**: Stack (LIFO)
- **Time Complexity**: O(V + E)
- **Guarantee**: Finds *a* path (not necessarily optimal)

## 🗺️ Metro Network

- **40 stations** across **5 lines** (Yellow, Blue, Red, Green, Violet)
- **5 interchange stations**: Kashmere Gate, Rajiv Chowk, Central Secretariat, Mandi House, Inderlok
- **41 bidirectional connections** with realistic distances (km) and times (min)

## 📊 Fare Slabs

| Distance | Fare |
|---|---|
| 0–2 km | ₹10 |
| 2–5 km | ₹20 |
| 5–12 km | ₹30 |
| 12–21 km | ₹40 |
| 21–32 km | ₹50 |
| 32+ km | ₹60 |

## 🧪 Tests

12 unit tests covering:
- Station creation & interchange detection
- Graph construction & adjacency list verification
- Dijkstra correctness (proves shorter path over direct route)
- BFS minimum-stops guarantee
- DFS path validity
- Fare calculation
- Edge cases (same source/dest, non-existent stations)
- Multi-line integration test
- Algorithm comparison (Dijkstra vs BFS trade-off)

## 📚 OOP Concepts Demonstrated

| Concept | Where |
|---|---|
| **Encapsulation** | Private data + public getters in all classes |
| **Composition** | MetroSystem HAS-A Graph and RoutePlanner |
| **Abstraction** | Simple `run()` interface hides complexity |
| **Operator Overloading** | `==` and `!=` in Station class |
| **Constructor Overloading** | Default + parameterized in Station |
| **Single Responsibility** | Each class handles one concern |
| **Modularity** | Separate headers/sources, extensible design |
