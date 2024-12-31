#include "reservation.h"

void BookingSystem::displayFlightDetailsR(const std::string& flightNumber) {
    auto it = flightMap.find(flightNumber);
    if (it != flightMap.end()) {
        Flight& flight = it->second;
        std::cout << "Flight Number: " << flight.flight_number << std::endl;

        std::cout << "\nAvailable seat numbers for the flight " << flightNumber << " are:\n";
        displayAvailableSeats();

        std::string chosenSeatNumber;
        std::cout << "Choose a seat number: ";
        std::getline(std::cin, chosenSeatNumber);
        flight.bookSeat(chosenSeatNumber);

        std::cout << "\nAvailable meals for the flight " << flightNumber << " are:\n";
        displayMealOptions();

        int chosenMealIndex;
        std::cout << "Choose a meal by entering the number: ";
        std::cin >> chosenMealIndex;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string chosenMeal;
        switch (chosenMealIndex) {
            case 1: chosenMeal = "Vegetarian"; break;
            case 2: chosenMeal = "Non-Vegetarian"; break;
            case 3: chosenMeal = "Vegan"; break;
            case 4: chosenMeal = "Gluten-Free"; break;
            default: chosenMeal = "Unknown"; break;
        }

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
        //std::cout << "Flight not found." << std::endl;
    }
}

void BookingSystem::displayAvailableSeats() {
    std::cout << "Available seat numbers are from 1 to 150:\n";
    for (int seat = 1; seat <= 150; ++seat) {
        std::cout << seat << " ";
    }
    std::cout << std::endl;
}

void BookingSystem::displayMealOptions() {
    std::cout << "Available meal options are:\n";
    std::cout << "1. Vegetarian\n";
    std::cout << "2. Non-Vegetarian\n";
    std::cout << "3. Vegan\n";
    std::cout << "4. Gluten-Free\n";
}
