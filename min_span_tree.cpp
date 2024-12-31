#include "min_span_tree.h"

// Helper function to get city index for both India and Australia trips
int getCityIndex(std::string city, std::string country) {
    if (country == "India") {
        if (city == "Gujarat") return 0;
        if (city == "Delhi") return 1;
        if (city == "Assam") return 2;
        if (city == "Bhopal") return 3;
        if (city == "Mumbai") return 4;
        if (city == "Chennai") return 5;
    } else if (country == "Australia") {
        if (city == "Perth") return 0;
        if (city == "Adelaide") return 1;
        if (city == "Melbourne") return 2;
        if (city == "Darwin") return 3;
        if (city == "Townsville") return 4;
    }
    return -1;
}

// Function to view India flight plans
void viewIndiaPlans() {
    Graph g(6);
    Flight flights[] = {
        {"GU101", "Delhi", "Gujarat", 100, 950, "Air India", "06:00", "08:00", 150},
        {"GU102", "Gujarat", "Bhopal", 120, 600, "SpiceJet", "09:00", "10:30", 100},
        {"GU103", "Gujarat", "Mumbai", 200, 400, "IndiGo", "11:00", "12:00", 200},
        {"DE104", "Assam", "Delhi", 110, 1700, "Air India", "07:00", "10:00", 180},
        {"BH105", "Bhopal", "Assam", 130, 1600, "GoAir", "08:00", "11:00", 150},
        {"BH106", "Bhopal", "Mumbai", 70, 700, "Vistara", "06:00", "07:00", 120},
        {"BH107", "Bhopal", "Chennai", 80, 1200, "IndiGo", "12:00", "14:00", 100},
        {"MU108", "Mumbai", "Chennai", 50, 1330, "SpiceJet", "10:00", "11:30", 90},
        {"AS109", "Assam", "Chennai", 125, 1800, "Air India", "15:00", "18:00", 110}
    };

    for (auto& flight : flights) {
        int fromIndex = getCityIndex(flight.from, "India");
        int toIndex = getCityIndex(flight.to, "India");
        g.addEdge(fromIndex, toIndex, flight.cost, flight);
    }

    g.kruskals_mst();
}

// Function to view Australia flight plans
void viewAustraliaPlans() {
    Graph g(5);
    // Dummy flights for Australia trip
    Flight flights[] = {
        {"AU101", "Perth", "Adelaide", 80, 2700, "Qantas", "06:00", "09:30", 150},
        {"AU102", "Darwin", "Perth", 50, 3200, "Virgin Australia", "10:00", "13:30", 100},
        {"AU103", "Adelaide", "Melbourne", 110, 1400, "Jetstar", "14:00", "15:30", 200},
        {"AU104", "Adelaide", "Darwin", 90, 3000, "Tigerair", "16:00", "19:30", 180},
        {"AU105", "Melbourne", "Townsville", 70, 2500, "Qantas", "20:00", "23:00", 150},
        {"AU106", "Darwin", "Melbourne", 150, 2900, "Virgin Australia", "07:00", "10:30", 150},
        {"AU107", "Townsville", "Darwin", 100, 2600, "Jetstar", "11:00", "14:00", 180}
    };

    for (auto& flight : flights) {
        int fromIndex = getCityIndex(flight.from, "Australia");
        int toIndex = getCityIndex(flight.to, "Australia");
        g.addEdge(fromIndex, toIndex, flight.cost, flight);
    }

    g.kruskals_mst();
}
