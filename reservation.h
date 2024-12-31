#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include "flight_search.h"  // Include the flight_search.h header

class Meal {
private:
    std::string name;

public:
    Meal(std::string meal_name) : name(meal_name) {}

    std::string getName() const { return name; }
};

class Passenger {
private:
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
    std::string nationality;
    std::string mobileNumber;
    std::string emailAddress;
    std::string gender;
    bool isAdult;

public:
    Passenger(std::string first, std::string last, std::string dob, std::string nation, std::string mobile, std::string email, std::string gen, bool adult)
        : firstName(first), lastName(last), dateOfBirth(dob), nationality(nation), mobileNumber(mobile), emailAddress(email), gender(gen), isAdult(adult) {}

    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getDateOfBirth() const { return dateOfBirth; }
    std::string getNationality() const { return nationality; }
    std::string getMobileNumber() const { return mobileNumber; }
    std::string getEmailAddress() const { return emailAddress; }
    std::string getGender() const { return gender; }
    bool getIsAdult() const { return isAdult; }

    void setFirstName(std::string first) { firstName = first; }
    void setLastName(std::string last) { lastName = last; }
    void setDateOfBirth(std::string dob) { dateOfBirth = dob; }
    void setNationality(std::string nation) { nationality = nation; }
    void setMobileNumber(std::string mobile) { mobileNumber = mobile; }
    void setEmailAddress(std::string email) { emailAddress = email; }
    void setGender(std::string gen) { gender = gen; }
    void setIsAdult(bool adult) { isAdult = adult; }
};

class Reservation {
private:
    std::vector<Passenger> passengers;
    std::vector<Flight> flights;
    std::string travelClass;
    int bookingID;
    bool isConfirmed = false;
    std::string seatNumber;
    std::string mealOption;

public:
    Reservation() {}

    Reservation(int id) : bookingID(id) {}

    void addPassenger(Passenger passenger) { passengers.push_back(passenger); }
    void addFlight(Flight flight) { flights.push_back(flight); }
    void setTravelClass(std::string travel_class) { travelClass = travel_class; }
    int getBookingID() const { return bookingID; }
    std::vector<Passenger>& getPassengers() { return passengers; }
    std::vector<Flight>& getFlights() { return flights; }
    std::string getTravelClass() const { return travelClass; }
    void setConfirmed(bool confirmed) { isConfirmed = confirmed; }
    bool getIsConfirmed() const { return isConfirmed; }
    void setSeatNumber(const std::string& seat) { seatNumber = seat; }
    std::string getSeatNumber() const { return seatNumber; }
    void setMealOption(const std::string& meal) { mealOption = meal; }
    std::string getMealOption() const { return mealOption; }
};

class BookingSystem {
private:
    std::vector<Reservation> reservations;
    std::stack<std::string> bookedFlightNumbers;
    std::unordered_map<int, Reservation> reservationMap;
    std::unordered_map<std::string, Flight> flightMap;

public:
    void createReservation(const std::string& passengerName, const std::string& flightNumber, int bookingID) {
        std::cout << "Reservation made for " << passengerName << " on flight " << flightNumber << " is successful." << std::endl;
        std::cout << "Booking ID: " << bookingID << std::endl;
    }

    void updateReservation(int bookingID) {
        auto it = reservationMap.find(bookingID);
        if (it != reservationMap.end()) {
            Reservation& reservation = it->second;
            std::vector<Passenger>& passengers = reservation.getPassengers();

            std::string firstName, lastName, dob, nationality, mobile, email, gender;
            std::cout << "Select the information you want to update:" << std::endl;
            std::cout << "1. First Name" << std::endl;
            std::cout << "2. Last Name" << std::endl;
            std::cout << "3. Date of Birth" << std::endl;
            std::cout << "4. Nationality" << std::endl;
            std::cout << "5. Mobile Number" << std::endl;
            std::cout << "6. Email Address" << std::endl;
            std::cout << "7. Gender" << std::endl;
            std::cout << "Enter your choice: ";
            int choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1:
                    std::cout << "Enter new First Name: ";
                    std::getline(std::cin, firstName);
                    passengers[0].setFirstName(firstName);
                    break;
                case 2:
                    std::cout << "Enter new Last Name: ";
                    std::getline(std::cin, lastName);
                    passengers[0].setLastName(lastName);
                    break;
                case 3:
                    std::cout << "Enter new Date of Birth (YYYY-MM-DD): ";
                    std::getline(std::cin, dob);
                    passengers[0].setDateOfBirth(dob);
                    break;
                case 4:
                    std::cout << "Enter new Nationality: ";
                    std::getline(std::cin, nationality);
                    passengers[0].setNationality(nationality);
                    break;
                case 5:
                    std::cout << "Enter new Mobile Number: ";
                    std::getline(std::cin, mobile);
                    passengers[0].setMobileNumber(mobile);
                    break;
                case 6:
                    std::cout << "Enter new Email Address: ";
                    std::getline(std::cin, email);
                    passengers[0].setEmailAddress(email);
                    break;
                case 7:
                    std::cout << "Enter new Gender: ";
                    std::getline(std::cin, gender);
                    passengers[0].setGender(gender);
                    break;
                default:
                    std::cout << "Invalid choice." << std::endl;
                    return;
            }

            std::cout << "Passenger details updated successfully:" << std::endl;
            std::cout << "First Name: " << passengers[0].getFirstName() << std::endl;
            std::cout << "Last Name: " << passengers[0].getLastName() << std::endl;
            std::cout << "Date of Birth: " << passengers[0].getDateOfBirth() << std::endl;
            std::cout << "Nationality: " << passengers[0].getNationality() << std::endl;
            std::cout << "Mobile Number: " << passengers[0].getMobileNumber() << std::endl;
            std::cout << "Email Address: " << passengers[0].getEmailAddress() << std::endl;
            std::cout << "Gender: " << passengers[0].getGender() << std::endl;
        } else {
            std::cout << "Reservation not found." << std::endl;
        }
    }

    void cancelReservation(int bookingID) {
        auto it = reservationMap.find(bookingID);
        if (it != reservationMap.end()) {
            Reservation& reservation = it->second;
            reservationMap.erase(it);

            std::vector<Flight>& flights = reservation.getFlights();
            for (const Flight& flight : flights) {
                bookedFlightNumbers.push(flight.flight_number);
            }

            std::cout << "Reservation canceled successfully." << std::endl;
        } else {
            std::cout << "Reservation not found." << std::endl;
        }
    }

    void addReservation(const Reservation& reservation) {
        reservations.push_back(reservation);
        reservationMap[reservation.getBookingID()] = reservation;
    }

    void addFlight(const Flight& flight) {
        flightMap[flight.flight_number] = flight;
    }
    void displayFlightDetailsR(const std::string& flightNumber);
   void displayAvailableSeats(const std::string& flightNumber);  // Add this declaration

    void displayMealOptions(const std::string& flightNumber);
        void displayAvailableSeats();
    void displayMealOptions();
    void confirmReservation(int bookingID);
 /*   void displayFlightDetailsR(const std::string& flightNumber) {
 auto it = flightMap.find(flightNumber);
    if (it != flightMap.end()) {
        Flight& flight = it->second;
        std::cout << "Flight Number: " << flight.flight_number << std::endl;

        std::cout << "\nAvailable seat numbers for the flight " << flightNumber << " are:\n";
        std::vector<int> availableSeatNumbers = flight.getAvailableSeatNumbers();
        for (const auto& seat : availableSeatNumbers) {
            std::cout << seat << " ";
        }
        std::cout << std::endl;

        std::string chosenSeatNumber;
        std::cout << "Choose a seat number: ";
        std::getline(std::cin, chosenSeatNumber);
        flight.bookSeat(chosenSeatNumber);

        std::cout << "\nAvailable meals for the flight " << flightNumber << " are:\n";
        std::vector<std::string> availableMeals = flight.getAvailableMeals();
        for (size_t j = 0; j < availableMeals.size(); ++j) {
            std::cout << j + 1 << ". " << availableMeals[j] << std::endl;
        }

            int chosenMealIndex;
            std::cout << "Choose a meal by entering the number: ";
            std::cin >> chosenMealIndex;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            //std::string chosenMeal = availableMeals[chosenMealIndex - 1].getName();
std::string chosenMeal = availableMeals[chosenMealIndex - 1];

            // Example of adding reservation after selecting seat and meal
            int bookingID = reservations.size() + 1;
            Reservation reservation(bookingID);
            Passenger passenger("John", "Doe", "1990-01-01", "USA", "1234567890", "john.doe@example.com", "Male", true);
            reservation.addPassenger(passenger);
            reservation.addFlight(flight);
            reservation.setSeatNumber(chosenSeatNumber);
            reservation.setMealOption(chosenMeal);
            reservation.setConfirmed(true);

            createReservation(passenger.getFirstName() + " " + passenger.getLastName(), flightNumber, bookingID);
            addReservation(reservation);
        } else {
            std::cout << "Flight not found." << std::endl;
        }
    }*/
};

#endif // RESERVATION_H

