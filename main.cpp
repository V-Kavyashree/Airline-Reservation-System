#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include "flight_search.h"
#include "login.h"
#include "app.h"
#include "floyd_warshall.h"
#include "min_span_tree.h" 
#include "admin.h" 
#include "reservation.h" 
using namespace std;

BookingSystem bookingSystem; // Declare BookingSystem object globally or pass it around as needed

void gatherPassengerDetails(Passenger& passenger) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string firstName, lastName, dob, nationality, mobile, email, gender;
    bool isAdult;

    cout << "Enter passenger details:" << endl;
    cout << "First Name: ";
    getline(cin, firstName);
    cout << "Last Name: ";
    getline(cin, lastName);
    cout << "Date of Birth (YYYY-MM-DD): ";
    getline(cin, dob);
    cout << "Nationality: ";
    getline(cin, nationality);
    cout << "Mobile Number: ";
    getline(cin, mobile);
    cout << "Email Address: ";
    getline(cin, email);
    cout << "Gender: ";
    getline(cin, gender);
    cout << "Is the passenger an adult? (1 for yes, 0 for no): ";
    cin >> isAdult;

    passenger = Passenger(firstName, lastName, dob, nationality, mobile, email, gender, isAdult);
}

void searchFlights(const string& from, const string& to) {
    vector<Flight> flights;
    unordered_map<string, vector<Flight>> flightMap;
    readFlightsFromFile("flights.txt", flights, flightMap);

    vector<Flight> flightsFrom = searchFlightsByFrom(flightMap, from);
    if (flightsFrom.empty()) {
        cout << "No flights found from " << from << "." << endl;
        return;
    }

    vector<Flight> flightsTo = searchFlightsByTo(flightsFrom, to);
    if (flightsTo.empty()) {
        cout << "No flights found from " << from << " to " << to << "." << endl;
        return;
    }

    while (true) {
        cout << "Flights from " << from << " to " << to << ":" << endl;
        printFlights(flightsTo);

        cout << "Choose an option:" << endl;
        cout << "1. Cheapest flights" << endl;
        cout << "2. Earliest departing flights" << endl;
        cout << "3. Cost-efficient route" << endl;
        cout << "4. Make a reservation" << endl; // Added reservation option
        cout << "5. Exit to main menu" << endl; // Updated exit option
        int option;
        cin >> option;

        if (option == 1 || option == 2) {
            bool sortByCost = (option == 1);
            AVLTree avlTree;
            for (const Flight& flight : flightsTo) {
                avlTree.insert(flight);
            }
            vector<Flight> sortedFlights = avlTree.getSortedFlights();
            if (sortByCost) {
                sort(sortedFlights.begin(), sortedFlights.end(), [](const Flight& a, const Flight& b) {
                    return a.cost < b.cost;
                });
                cout << "Cheapest flights from " << from << " to " << to << ":" << endl;
            } else {
                sort(sortedFlights.begin(), sortedFlights.end(), [](const Flight& a, const Flight& b) {
                    return a.departure_time < b.departure_time;
                });
                cout << "Earliest departing flights from " << from << " to " << to << ":" << endl;
            }
            printFlights(sortedFlights);
        } else if (option == 3) {
            displayCheapestRoute(from, to);
        } else if (option == 4) {
            // Reservation logic
            cout << "Enter the flight number for reservation: ";
            string flightNumber;
            cin >> flightNumber;

            auto it = find_if(flightsTo.begin(), flightsTo.end(), [&flightNumber](const Flight& flight) {
                return flight.flight_number == flightNumber;
            });

            if (it != flightsTo.end()) {
                Passenger passenger("", "", "", "", "", "", "", false);
                gatherPassengerDetails(passenger);

                // Display available seats and allow the passenger to select one
                cout << "Available seats for flight " << flightNumber << ":" << endl;
                bookingSystem.displayFlightDetailsR(flightNumber);
                
                for (int seat = 1; seat <= 150; ++seat) {
        std::cout << seat << " ";
        if(seat%10==0){
            cout<<"\n";
        }
    }
                string selectedSeat;
                cout << "Select a seat: ";
                cin >> selectedSeat;

                // Display available meal options and allow the passenger to select one
                cout << "Available meal options for flight \n" << flightNumber << ":" << endl;
                    std::cout << "1. Vegetarian\n";
    std::cout << "2. Non-Vegetarian\n";
    std::cout << "3. Vegan\n";
    std::cout << "4. Gluten-Free\n";
             //   displayAvailableMeals(flightNumber);
                string selectedMeal;
                cout << "Select a meal: ";
                cin >> selectedMeal;

                int bookingID = rand() % 10000; // Generate a random booking ID
                Reservation reservation(bookingID);
                reservation.addPassenger(passenger);
                reservation.addFlight(*it);
                reservation.setTravelClass("Economy"); // Default travel class
                reservation.setSeatNumber(selectedSeat); // Set selected seat
                reservation.setMealOption(selectedMeal); // Set selected meal

                bookingSystem.addReservation(reservation);
                bookingSystem.createReservation(passenger.getFirstName() + " " + passenger.getLastName(), flightNumber, bookingID);

               // bookingSystem.displayFlightDetailsR(flightNumber);
                       //bookingSystem.displayAvailableSeats(flightNumber);
      //  bookingSystem.displayMealOptions(flightNumber);
    //  displayAvailableSeats(flightNumber);
     //           displayMealOptions(flightNumber);
                cout << "Reservation made successfully." << endl;

                // After reservation, offer options to update, cancel, or return to main menu
                while (true) {
                    cout << "Choose an option:" << endl;
                    cout << "1. Update reservation" << endl;
                    cout << "2. Cancel reservation" << endl;
                    cout<<"3.confirm ticket"<<endl;
                    cout << "4. Return to main menu" << endl;
                    int reservationOption;
                    cin >> reservationOption;

                    if (reservationOption == 1) {
                        // Update reservation logic
                        int bookingID;
                        cout << "Enter Booking ID: ";
                        cin >> bookingID;
                        bookingSystem.updateReservation(bookingID);
                    } else if (reservationOption == 2) {
                        // Cancel reservation logic
                        int bookingID;
                        cout << "Enter Booking ID: ";
                        cin >> bookingID;
                        bookingSystem.cancelReservation(bookingID);
                    } 
                    else if (reservationOption == 3) {
                        cout<<"MAKE PAYMENT\n"<<endl;
                        
                                    // Assuming a static price for simplicity
            const double p= 150.00;
            cout << "Ticket Price: $" << p << endl;

            // Transaction
            double amountPaid;
            cout << "Enter the amount to pay: $";
            cin >> amountPaid;

            if (amountPaid >= p) {
                cout << "Transaction successful." << endl;
            } else {
                cout << "Transaction failed. Amount paid is less than ticket price." << endl;
            }
                std::cout << "-------------------------------\n";
    std::cout << "          Flight Ticket        \n";
    std::cout << "-------------------------------\n";
    std::cout << "Flight No: BA710\n";
    std::cout << "Name: Abi\n";
    std::cout << "Amount: $150\n";
    std::cout << "From: Paris\n";
    std::cout << "To: London\n";
    std::cout << "Departing: 11:00\n";
    std::cout << "Reaching: 16:00\n";
    std::cout << "Airline: ABC Airline\n";
    std::cout << "-------------------------------\n";
    std::cout << "THANK YOU\n";
    
                        break; // wanna call confirm ticket option!!
                    }
                    else if (reservationOption == 4) {
                        break; // Return to main menu
                    } else {
                        cout << "Invalid option. Please try again." << endl;
                    }
                }
            } else {
                cout << "Invalid flight number. Please try again." << endl;
            }
        } else if (option == 5) {
            break; // Exit the loop and return to the main menu
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }
}


int main() {
    setupFloydWarshall("flights.txt"); 
    while (true) {
        int choice;
        cout << "\n\n\t\t\t\t********** WELCOME TO THE FLIGHT RESERVATION SYSTEM **********\n\n";
        cout << "\t\t\t\t1. LOGIN\n";
        cout << "\t\t\t\t2. REGISTER\n";
        cout << "\t\t\t\t3. FORGOT PASSWORD (or) USERNAME\n";
        cout << "\t\t\t\t4. VIEW PLANS\n";
        cout << "\t\t\t\t5. ADMIN LOGIN\n";
        cout << "\t\t\t\t6. EXIT\n";
        cout << "\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                    if (login()) { // Ensure login is successful
                    string from, to;
                    cout << "Enter the departure location: ";
                    cin >> from;
                    cout << "Enter the destination location: ";
                    cin >> to;
                    searchFlights(from, to);
                }
                break;
            case 2:
                registration();
                break;
            case 3:
                forgot();
                break;
            case 4:
                cout << "\nChoose a trip plan:\n";
                cout << "1. India Trip\n";
                cout << "2. Australia Trip\n";
                int planChoice;
                cin >> planChoice;
                if (planChoice == 1) {
                    viewIndiaPlans();
                } else if (planChoice == 2) {
                    viewAustraliaPlans();
                } else {
                    cout << "Invalid choice. Returning to main menu.\n";
                }
                break;
            case 5:
                if (adminLogin()) {
                    adminMenu();
                }
                break;
            case 6:
                cout << "\n\n\t\t\t\tThank you! Have a nice day!\n\n";
                return 0;
            default:
                cout << "\n\n\t\t\t\tInvalid choice! Please try again.\n\n";
        }
    }
    return 0;
}
