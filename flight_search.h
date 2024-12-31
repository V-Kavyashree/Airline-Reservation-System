#ifndef FLIGHT_SEARCH_H
#define FLIGHT_SEARCH_H
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

struct Flight {
    std::string flight_number;
    std::string from;
    std::string to;
    double cost;
    double distance;
    std::string name;
    std::string departure_time;
    std::string arrival_time;
    int available_seats;
    std::vector<int> available_seat_numbers; // New member variable to store available seat numbers
    std::vector<std::string> available_meals; // New member variable to store available meals
    
    Flight() : cost(0.0), distance(0.0), available_seats(0) {}
    
    Flight(std::string fn, std::string f, std::string t, double c, double d, std::string n, std::string dt, std::string at, int as)
        : flight_number(fn), from(f), to(t), cost(c), distance(d), name(n), departure_time(dt), arrival_time(at), available_seats(as) {}
    
    std::string flightDetailsToString() const {
        return flight_number + "," + from + "," + to + "," + std::to_string(cost) + "," + std::to_string(distance) + "," + name + "," + departure_time + "," + arrival_time + "," + std::to_string(available_seats);
    }
    
    void displayFlightDetails() const {
        std::cout << "Flight Number: " << flight_number << std::endl;
        std::cout << "From: " << from << std::endl;
        std::cout << "To: " << to << std::endl;
        std::cout << "Cost: " << cost << std::endl;
        std::cout << "Distance: " << distance << std::endl;
        std::cout << "Airline Name: " << name << std::endl;
        std::cout << "Departure Time: " << departure_time << std::endl;
        std::cout << "Arrival Time: " << arrival_time << std::endl;
        std::cout << "Available Seats: " << available_seats << std::endl;
        std::cout << "Available Seat Numbers: ";
        for (const auto& seat : available_seat_numbers) {
            std::cout << seat << " ";
        }
        std::cout << std::endl;
        std::cout << "Available Meals: ";
        for (const auto& meal : available_meals) {
            std::cout << meal << " ";
        }
        std::cout << std::endl;
    }
void bookSeat(const std::string& seatNumber) {
    // Convert seatNumber to integer
    int seatToRemove = std::stoi(seatNumber);

    // Remove the seat from available_seat_numbers
    available_seat_numbers.erase(
        std::remove_if(
            available_seat_numbers.begin(), 
            available_seat_numbers.end(), 
            [seatToRemove](int seat) { return seat == seatToRemove; }
        ), 
        available_seat_numbers.end()
    );

    // Decrement available seats count
    available_seats--;
}

std::vector<std::string> getAvailableMeals() const {
    return available_meals;
}
    // Member function to get available seat numbers
    std::vector<int> getAvailableSeatNumbers() const {
        return available_seat_numbers;
    }

   
};

// Function declarations
void readFlightsFromFile(const std::string& filename, std::vector<Flight>& flights, std::unordered_map<std::string, std::vector<Flight>>& flightMap);
std::vector<Flight> searchFlightsByFrom(const std::unordered_map<std::string, std::vector<Flight>>& flightMap, const std::string& from);
std::vector<Flight> searchFlightsByTo(const std::vector<Flight>& flightsFrom, const std::string& to);
void printFlights(const std::vector<Flight>& flights);
 //void displayFlightDetailsR(const std::string& flightNumber);

class AVLTree {
public:
    AVLTree();
    void insert(const Flight& flight);
    std::vector<Flight> getSortedFlights(bool sortByCost = false);

private:
    struct AVLNode {
        Flight flight;
        AVLNode* left;
        AVLNode* right;
        int height;
        AVLNode(const Flight& f) : flight(f), left(nullptr), right(nullptr), height(1) {}
    };

    AVLNode* root;

    int height(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insertRec(AVLNode* node, const Flight& flight);
    void inorderRec(AVLNode* root, std::vector<Flight>& flights, bool sortByCost);
};



#endif // FLIGHT_SEARCH_H
