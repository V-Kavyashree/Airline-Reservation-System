#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include "flight_search.h" // Include the Flight class and other necessary declarations

using namespace std;

struct FlightComparator {
    bool operator()(Flight* const& f1, Flight* const& f2) {
        return f1->cost > f2->cost; // Example: prioritize by cost, modify as needed
    }
};

class FlightHeap {
private:
    priority_queue<Flight*, vector<Flight*>, FlightComparator> flights; // Priority queue of Flight pointers
    unordered_set<string> deletedFlights; // Set to store deleted flight numbers

public:
    void addFlight(Flight* flight) {
        flights.push(flight);
    }

    Flight* findAndRemoveFlight(const string& flight_number) {
        priority_queue<Flight*, vector<Flight*>, FlightComparator> temp; // Temporary priority queue to store remaining flights
        Flight* foundFlight = nullptr;
        while (!flights.empty()) {
            if (flights.top()->flight_number == flight_number) {
                foundFlight = flights.top(); // Flight to delete is found
                deletedFlights.insert(flight_number); // Add flight number to deleted flights set
            } else {
                temp.push(flights.top()); // Keep all flights except the one to be deleted
            }
            flights.pop();
        }
        flights = temp; // Update the main priority queue with the remaining flights
        return foundFlight;
    }

    void displayFlights() const {
        priority_queue<Flight*, vector<Flight*>, FlightComparator> temp = flights; // Copy of priority queue for display
        while (!temp.empty()) {
            temp.top()->displayFlightDetails();
            temp.pop();
        }
    }

    void deleteFlightFromFile(const string& flight_number) {
        ifstream inputFile("flights.txt");
        ofstream outputFile("temp_flights.txt");

        if (!inputFile.is_open() || !outputFile.is_open()) {
            cout << "Error: Unable to open file for reading/writing." << endl;
            return;
        }

        string line;
        while (getline(inputFile, line)) {
            // Check if the line starts with the flight number followed by a comma
            if (line.substr(0, flight_number.size() + 1) != flight_number + ",") {
                outputFile << line << endl; // Write all lines except the one to delete
            }
        }

        inputFile.close();
        outputFile.close();

        // Replace the original file with the updated file
        remove("flights.txt");
        rename("temp_flights.txt", "flights.txt");
    }

    const unordered_set<string>& getDeletedFlights() const {
        return deletedFlights;
    }
};

bool adminLogin() {
    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    // Simple hardcoded authentication for example purposes
    if (username == "admin" && password == "password") {
        return true;
    } else {
        cout << "Invalid admin credentials. Access denied." << endl;
        return false;
    }
}

void adminMenu() {
    FlightHeap flightHeap;

    while (true) {
        int choice;
        cout << "\n\n\t\t\t\t********** ADMIN MENU **********\n\n";
        cout << "\t\t\t\t1. Add Flight\n";
        cout << "\t\t\t\t2. Delete Flight\n";
        cout << "\t\t\t\t3. Display Flights\n";
        cout << "\t\t\t\t4. Exit to main menu\n";
        cout << "\t\t\t\tEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string flight_number, departure_airport, arrival_airport, departure_time, arrival_time, airline_name;
            double price;
            double distance;
            int seat_availability;

            cout << "Enter Flight Number: ";
            cin >> flight_number;
            cout << "Enter Departure Airport: ";
            cin >> departure_airport;
            cout << "Enter Arrival Airport: ";
            cin >> arrival_airport;
            cout << "Enter Departure Time: ";
            cin >> departure_time;
            cout << "Enter Arrival Time: ";
            cin >> arrival_time;
                        cout << "Enter Airline: ";
            cin >> airline_name;
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Distance: ";
            cin >> distance;
            cout << "Enter Seat Availability: ";
            cin >> seat_availability;

            Flight* flight = new Flight(flight_number, departure_airport, arrival_airport, price, distance, airline_name, departure_time, arrival_time, seat_availability);
            flightHeap.addFlight(flight);

            // Open a file to append flight details
            ofstream outputFile("flights.txt", ios::app);
            if (!outputFile.is_open()) {
                cout << "Error: Unable to open file for writing." << endl;
            } else {
                outputFile << flight->flightDetailsToString() << endl;
                outputFile.close();
            }
        } else if (choice == 2) {
            string flight_number;
            cout << "Enter Flight Number to delete: ";
            cin >> flight_number;

            Flight* flight = flightHeap.findAndRemoveFlight(flight_number);
            if (flight) {
                flightHeap.deleteFlightFromFile(flight_number);
                cout << "Flight " << flight_number << " deleted successfully." << endl;
            } else {
                cout << "Flight not found." << endl;
            }
        } else if (choice == 3) {
            flightHeap.displayFlights();
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

#endif // ADMIN_H
