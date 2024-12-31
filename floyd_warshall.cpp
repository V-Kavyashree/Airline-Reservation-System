#include "floyd_warshall.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;

std::unordered_map<std::string, int> cityIndex;
std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> nextHop; // Renamed to nextHop
std::unordered_map<int, std::vector<Flight>> flightMap;

//const int INF = numeric_limits<int>::max();

void setupFloydWarshall(const std::string& filename) {
    vector<Flight> flights;
    unordered_map<string, vector<Flight>> tempFlightMap; // Temporary flight map for reading flights

    readFlightsFromFile(filename, flights, tempFlightMap);

    for (const auto& flight : flights) {
        if (cityIndex.find(flight.from) == cityIndex.end()) {
            cityIndex[flight.from] = cityIndex.size();
        }
        if (cityIndex.find(flight.to) == cityIndex.end()) {
            cityIndex[flight.to] = cityIndex.size();
        }
    }

    int n = cityIndex.size();
    graph.resize(n, vector<int>(n, INF));
    nextHop.resize(n, vector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
        graph[i][i] = 0;
        nextHop[i][i] = i;
    }

    for (const auto& flight : flights) {
        int u = cityIndex[flight.from];
        int v = cityIndex[flight.to];
        if (graph[u][v] > flight.cost) {
            graph[u][v] = flight.cost;
            nextHop[u][v] = v;
        }
        flightMap[u].push_back(flight);
    }

    floydWarshall(graph, nextHop);
}

void floydWarshall(std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& nextHop) {
    int n = graph.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (graph[i][k] != INF && graph[k][j] != INF && graph[i][j] > graph[i][k] + graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    nextHop[i][j] = nextHop[i][k];
                }
            }
        }
    }
}

std::vector<int> reconstructPath(int u, int v, const std::vector<std::vector<int>>& nextHop) {
    if (nextHop[u][v] == -1) {
        return {};
    }
    std::vector<int> path = {u};
    while (u != v) {
        u = nextHop[u][v];
        path.push_back(u);
    }
    return path;
}

void displayFlightDetails(const Flight& flight) {
    cout << flight.flight_number << " | " << flight.from << " -> " << flight.to << " | Cost: " << flight.cost
         << " | Distance: " << flight.distance << " | Airline: " << flight.name
         << " | Departure: " << flight.departure_time << " | Arrival: " << flight.arrival_time
         << " | Seats: " << flight.available_seats << endl;
}

void displayCheapestRoute(const std::string& fromCity, const std::string& toCity) {
    if (cityIndex.find(fromCity) == cityIndex.end() || cityIndex.find(toCity) == cityIndex.end()) {
        cout << "Invalid cities entered." << endl;
        return;
    }

    int u = cityIndex[fromCity];
    int v = cityIndex[toCity];

    if (graph[u][v] == INF) {
        cout << "No route from " << fromCity << " to " << toCity << endl;
    } else {
        cout << "Cheapest route from " << fromCity << " to " << toCity << " costs " << graph[u][v] << endl;
        vector<int> path = reconstructPath(u, v, nextHop);
        for (size_t i = 0; i < path.size() - 1; ++i) {
            int fromIndex = path[i];
            int toIndex = path[i + 1];
            for (const auto& flight : flightMap[fromIndex]) {
                if (cityIndex[flight.to] == toIndex && flight.cost == graph[fromIndex][toIndex]) {
                    displayFlightDetails(flight);
                    break;
                }
            }
        }
    }
}
