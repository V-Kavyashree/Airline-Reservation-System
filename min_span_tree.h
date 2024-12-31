#ifndef MIN_SPAN_TREE_H
#define MIN_SPAN_TREE_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>
#include "flight_search.h" // Assuming Flight struct is defined here

class DSU {
    int* parent;
    int* rank;
public:
    DSU(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }
    int find(int i) {
        if (parent[i] == -1)
            return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int x, int y) {
        int s1 = find(x);
        int s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
            } else if (rank[s1] > rank[s2]) {
                parent[s2] = s1;
            } else {
                parent[s2] = s1;
                rank[s1] += 1;
            }
        }
    }
};

class Graph {
    std::vector<std::vector<int>> edgelist;
    int V;
    std::unordered_map<int, Flight> flight_map;
public:
    Graph(int V) { this->V = V; }
    void addEdge(int x, int y, int w, Flight flight) {
        edgelist.push_back({w, x, y});
        flight_map[1000 * x + y] = flight;
    }
    void kruskals_mst() {
        sort(edgelist.begin(), edgelist.end());
        DSU s(V);
        double ans = 0;
        std::cout << "Following are the cost efficiant route" << std::endl;
        for (auto edge : edgelist) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];
            if (s.find(x) != s.find(y)) {
                s.unite(x, y);
                ans += w;
                Flight flight = flight_map[1000 * x + y];
                std::cout << "Flight: " << flight.flight_number << ", From: " << flight.from << ", To: " << flight.to << ", Cost: " << flight.cost << std::endl;
            }
        }
        std::cout << "Total cost:Rs." << ans << std::endl;
    }
};

// Helper functions
int getCityIndex(std::string city, std::string country);

void viewIndiaPlans();
void viewAustraliaPlans();

#endif // MIN_SPAN_TREE_H
