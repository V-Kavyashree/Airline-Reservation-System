#include "login.h"
#include "flight_search.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "app.h"

using namespace std;

bool login() {
    int count = 0;
    string userId, password, id, pass, storedName, storedDob;
    system("cls");
    cout << "\t\t\t Please enter the username and password: " << endl;
    cout << "\t\t\t USERNAME: ";
    cin >> userId;
    cout << "\t\t\t PASSWORD: ";
    cin >> password;

    ifstream input("registration.txt");
    while (input >> id >> pass >> storedName >> storedDob) {
        if (id == userId && pass == password) {
            count = 1;
            break;
        }
    }
    input.close();

    if (count == 1) {
        cout << "\nLogin successful! Welcome " << storedName << "!\n";
        return true;
    } else {
        int option;
        cout << "\nLogin failed! Invalid username or password.\n";
        cout << "Press 1 if you forgot your password\n";
        cout << "Press 2 to try login again\n";
        cout << "\t\t\t Enter your choice: ";
        cin >> option;
        if (option == 1) {
            forgot();
            return false;
        } else {
            return false;
        }
    }
}
void registration() {
    string ruserId, rpassword, rname, rdob;
    system("cls");
    cout << "\t\t\t Enter the username: ";
    cin >> ruserId;
    cout << "\t\t\t Enter the password: ";
    cin >> rpassword;
    cout << "\t\t\t Enter your name: ";
    cin.ignore();
    getline(cin, rname);
    cout << "\t\t\t Enter your date of birth (dd-mm-yyyy): ";
    cin >> rdob;

    ofstream f1("registration.txt", ios::app);
    f1 << ruserId << ' ' << rpassword << ' ' << rname << ' ' << rdob << endl;
    f1.close();
    system("cls");
    cout << "\n\t\t\t Registration is successful! \n";
    login();
}

void forgot() {
    int option;
    system("cls");
    cout << "\t\t\t You forgot the password? No worries \n";
    cout << "Press 1 to search your id by username " << endl;
    cout << "Press 2 to go back to the main menu " << endl;
    cout << "\t\t\t Enter your choice: ";
    cin >> option;

    switch (option) {
        case 1: {
            int count = 0;
            string suserId, sId, spass, storedName, storedDob;
            cout << "\n\t\t\t Enter the username you remember: ";
            cin >> suserId;

            ifstream f2("registration.txt");
            while (f2 >> sId >> spass >> storedName >> storedDob) {
                if (sId == suserId) {
                    count = 1;
                    break;
                }
            }
            f2.close();

            if (count == 1) {
                cout << "\n\n Your account is found! \n";
                cout << "\n\n Your password is: " << spass << endl;
            } else {
                cout << "\n\t Sorry! Your account is not found! \n";
            }
            break;
        }
        case 2:
            break;
        default:
            cout << "\t\t\t Wrong choice! Please try again " << endl;
            forgot();
    }
}
