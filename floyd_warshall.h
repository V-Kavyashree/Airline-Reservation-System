#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include "flight_search.h" // Include flight search functionalities

const int INF = std::numeric_limits<int>::max();

extern std::unordered_map<std::string, int> cityIndex;
extern std::vector<std::vector<int>> graph;
extern std::vector<std::vector<int>> next;
extern std::unordered_map<int, std::vector<Flight>> flightMap;

void setupFloydWarshall(const std::string& filename);
void floydWarshall(std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& next);
std::vector<int> reconstructPath(int u, int v, const std::vector<std::vector<int>>& next);
void displayCheapestRoute(const std::string& fromCity, const std::string& toCity);

#endif // FLOYD_WARSHALL_H
