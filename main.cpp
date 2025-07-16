#include <iostream>
#include "string"
#include "limits"
#include "./src/utils.h"
#include "./src/menu-manager.cpp"
#include "./src/order-manager.cpp"
using namespace std;

// Function declarations
void menuManagement();
void orderManagement();

//Main Menu for The Campus Crave
// This code provides a command-line interface for managing a cafeteria menu and it's orders.
int main() {
    int choice;
    do {

        cout << "Welcome to The Campus Crave!" << endl;
        cout << "Enjoy your meal :)" << endl;

        cout << "---------------------------------" << endl;
        cout << "---------------------------------" << endl;

        cout << "\n Main Menu" << endl;

        cout << "---------------------------------" << endl;
        cout << "---------------------------------" << endl;

        cout << "1. Menu Management" << endl;
        cout << "2. Order Management" << endl;
        cout << "3. Exit" << endl;

        cout << "---------------------------------" << endl;
        cout << "---------------------------------" << endl;

        cout << "Please select an option from the menu." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Menu Management Selected." << endl;
                menuManagement();
                break;
            case 2:
                cout << "Order Management Selected." << endl;
                orderManagement();
                break;
            case 3:
                cout << "Exiting the menu." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
