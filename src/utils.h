#include <iostream>
#include <string>
using namespace std;

// Structure to hold order details
struct Order {
    int orderId;
    int itemId;  // itemId to store the menu item associated with the order
    int totalItems;
    double totalPrice;
};

// Global variables
Order orders[50]; 
int totalOrders = 0;
int orderTotal = 0;
int totalItems = 0;

// Making this a global variable so its accessible in all functions
string itemNames[50] = {"Espresso", "Latte", "White Mocha", "Flat White", "Blueberry Lemonade",
                        "Margherita Pizza", "Shawarma", "Chicken Burger", "Focaccia", "French Fries", 
                        "Cheesecake", "Tiramisu"};
double itemPrices[50] = {2.50, 3.50, 2.50, 3.25, 2.75, 6.00, 4.75, 5.50, 3.50, 2.50, 4.00, 4.50};
int totalMenuItems = 12;
