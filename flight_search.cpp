#include "flight_search.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

void readFlightsFromFile(const string& filename, vector<Flight>& flights, unordered_map<string, vector<Flight>>& flightMap) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string flight_number, from, to, name, departure_time, arrival_time;
        double cost, distance;
        int available_seats;

        if (getline(ss, flight_number, ',') &&
            getline(ss, from, ',') &&
            getline(ss, to, ',') &&
            ss >> cost && ss.ignore(1, ',') &&
            ss >> distance && ss.ignore(1, ',') &&
            getline(ss, name, ',') &&
            getline(ss, departure_time, ',') &&
            getline(ss, arrival_time, ',') &&
            ss >> available_seats) {

            Flight flight(flight_number, from, to, cost, distance, name, departure_time, arrival_time, available_seats);
            flights.push_back(flight);
            flightMap[from].push_back(flight);
        } else {
            cout << "Error parsing line: " << line << endl;
        }
    }
}

vector<Flight> searchFlightsByFrom(const unordered_map<string, vector<Flight>>& flightMap, const string& from) {
    auto it = flightMap.find(from);
    if (it != flightMap.end()) {
        return it->second;
    } else {
        return {};
    }
}

vector<Flight> searchFlightsByTo(const vector<Flight>& flightsFrom, const string& to) {
    vector<Flight> flightsTo;
    for (const Flight& flight : flightsFrom) {
        if (flight.to == to) {
            flightsTo.push_back(flight);
        }
    }
    return flightsTo;
}

void printFlights(const vector<Flight>& flights) {
    for (const Flight& flight : flights) {
        cout << flight.flight_number << " | " << flight.from << " -> " << flight.to
             << " | Cost: " << flight.cost << " | Distance: " << flight.distance
             << " | Airline: " << flight.name << " | Departure: " << flight.departure_time
             << " | Arrival: " << flight.arrival_time << " | Seats: " << flight.available_seats << endl;
    }
}

// AVL Tree implementation
AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::height(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLTree::AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

AVLTree::AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

AVLTree::AVLNode* AVLTree::insertRec(AVLNode* node, const Flight& flight) {
    if (!node) return new AVLNode(flight);

    if (flight.departure_time < node->flight.departure_time ||
        (flight.departure_time == node->flight.departure_time && flight.cost < node->flight.cost)) {
        node->left = insertRec(node->left, flight);
    } else if (flight.departure_time > node->flight.departure_time ||
               (flight.departure_time == node->flight.departure_time && flight.cost > node->flight.cost)) {
        node->right = insertRec(node->right, flight);
    } else {
        return node; // Ignore duplicates
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && (flight.departure_time < node->left->flight.departure_time ||
                        (flight.departure_time == node->left->flight.departure_time && flight.cost < node->left->flight.cost))) {
        return rightRotate(node);
    }
    if (balance < -1 && (flight.departure_time > node->right->flight.departure_time ||
                         (flight.departure_time == node->right->flight.departure_time && flight.cost > node->right->flight.cost))) {
        return leftRotate(node);
    }
    if (balance > 1 && (flight.departure_time > node->left->flight.departure_time ||
                        (flight.departure_time == node->left->flight.departure_time && flight.cost > node->left->flight.cost))) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && (flight.departure_time < node->right->flight.departure_time ||
                         (flight.departure_time == node->right->flight.departure_time && flight.cost < node->right->flight.cost))) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(const Flight& flight) {
    root = insertRec(root, flight);
}

void AVLTree::inorderRec(AVLNode* root, vector<Flight>& flights, bool sortByCost) {
    if (root != nullptr) {
        inorderRec(root->left, flights, sortByCost);
        flights.push_back(root->flight);
        inorderRec(root->right, flights, sortByCost);
    }
}

vector<Flight> AVLTree::getSortedFlights(bool sortByCost) {
    vector<Flight> flights;
    inorderRec(root, flights, sortByCost);
    return flights;
}

