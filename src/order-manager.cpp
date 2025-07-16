#include <iostream>
#include <string>
using namespace std;

// External global variables (defined in utils.cpp)
extern Order orders[50];
extern int totalOrders;
extern int orderTotal;
extern string itemNames[50];
extern double itemPrices[50];
extern int totalMenuItems;

// External function from menu-manager.cpp
extern void menuList();

// Function declarations
void orderList();
void viewOrderDetails();
void deleteOrder();
void deleteOrderConfirmation(int index);
int viewAllOrders();
void createNewOrder(int currentOrderItems);
void addItemsToOrder(int itemId, int& currentOrderTotal, Order& currentOrder, int& totalItems, int& currentOrderItems);
void orderManagement();
void resetOrder(); 
void resetOrderConfirmation();

// Making order list global variable to use for view all orders function
void orderList() {
    cout << "| Order ID | Total Items | Total Price |" << endl;
    cout << "----------------------------------------------" << endl;

    for (int i = 0; i < totalOrders; i++) { // Loop through the orders
        cout << orders[i].orderId << " \t| "
             << orders[i].totalItems << " \t\t| €"
             << orders[i].totalPrice << endl;
    }

    cout << "----------------------------------------------" << endl;
    cout << "Total Orders: " << totalOrders << endl;
    cout << "Total Order Amount: €" << orderTotal << endl;
    cout << "----------------------------------------------" << endl;
}

void viewOrderDetails() {
    int orderId;

    cout << "-----------------------------" << endl;
    cout << "Enter Order ID to view details: ";
    cin >> orderId;

    if (orderId < 1 || orderId > totalOrders) {  // Validating order ID
        cout << "Invalid Order ID. Please try again." << endl;
        return;  // to avoid further execution of invalid input
    }

    // Display the order details
    cout << "Order ID: " << orders[orderId - 1].orderId << endl;  // Use orders array to get details
    cout << "Total Items: " << orders[orderId - 1].totalItems << endl;
    cout << "Total Price: €" << orders[orderId - 1].totalPrice << endl;

    cout << "\nThe Items in this order:\n" << endl; 

    // Find the actual number of different items in the order
    int itemCount = 0;
    for (int i = 0; i < 5; i++) {
        if (orders[orderId - 1].items[i].itemId != 0) {
            itemCount++;
        }
    }

    for (int idx = 0; idx < itemCount; idx++) {
        cout << "Item ID: " << orders[orderId - 1].items[idx].itemId << endl; 
        cout << "Item Name: " << itemNames[orders[orderId - 1].items[idx].itemId - 1] << endl;
        cout << "Quantity: " << orders[orderId - 1].items[idx].quantity << endl;
        cout << "-----" << endl;
    }

    cout << "Back to order management...\n" << endl; 

    orderManagement();
}

// Viewing total number of orders
int viewAllOrders() {
    int choice;

    do {
        cout << "---------------------------------" << endl;
        cout << "---------------------------------" << endl;

        cout << "\n View All Orders" << endl;

        orderList();

        cout << "---------------------------------" << endl;

        cout << " 1. View Order Details" << endl;
        cout << " 2. Order Management" << endl;
        cout << " 3. Back to Main Menu" << endl; 

        cout << "---------------------------------" << endl;
        cout << "---------------------------------" << endl;

        cout << "Enter your choice: " << endl;
        cin >> choice;

        switch (choice) {  
        case 1:
            cout << "Viewing Order Details..." << endl;
            viewOrderDetails(); 
            break;

        case 2:
            orderManagement();
            break;

        case 3:
            return 1;

        default:
            cout << "Invalid choice, please try again. " << endl; 
            break;
        }

    } while (choice != 3);
    return 0;
}


// Deleting orders confirmation
void deleteOrderConfirmation(int index){
    if (index < 0 || index >= totalOrders) {
        cout << "Invalid order index!" << endl;
        orderManagement();
        return;
    }

    int choice;

    while (true) {
        cout << "--------------------------------" << endl;
        cout << "--------------------------------" << endl;

        cout << "\n Confirm Order Deletion" << endl;

        cout << "--------------------------------" << endl;
        cout << "--------------------------------" << endl;

        cout << "Are you sure you want to delete this Order?" << endl;

        cout << "Order ID: " << orders[index].orderId << endl;
        cout << "Total Items: " << orders[index].totalItems << endl;
        cout << "Total Price: €" << orders[index].totalPrice << endl;

        cout << "This action cannot be undone!" << endl;
        cout << "--------------------------------" << endl;

        cout << "1. Yes, I want to delete this item" << endl;
        cout << "2. No, I want to cancel" << endl;

        cout << "--------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // Subtract the deleted order's total price from the global orderTotal
            orderTotal -= orders[index].totalPrice;
            for (int i = index; i < totalOrders - 1; i++) { // shifts orders to remove the selected one
                orders[i] = orders[i + 1];
            }
            totalOrders--;

            cout << "Your order has been successfully deleted!" << endl;
            break; // exits the loop and goes back to order management
        } else if (choice == 2) {
            cout << "Order deletion is cancelled." << endl;
            break; // exits the loop and goes back to order management
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    orderManagement();
}

// Delete orders
void deleteOrder(){
    int orderId;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "\n Delete Orders" << endl;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    orderList();
    cout << endl;

    cout << "WARNING: THIS ACTION CANNOT BE UNDONE!" << endl;
    cout << "Enter Order Id to delete (or 0 to go back): " << endl;

    cin >> orderId;

    if (orderId == 0) {
        cout << "Going back to Order Management..." << endl;
        return orderManagement();
    }

    if (orderId < 1 || orderId > totalOrders) {
        cout << "Invalid order Id, please try again." << endl;
        return;
    }
    int index = orderId - 1; //so the index starts from 0

    return deleteOrderConfirmation(index);
}

// Creating new order
void createNewOrder() {
    int itemId;
    int currentOrderTotal = 0; 
    int totalItems = 0;
    int currentOrderItems = 0;       

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    cout << "\n Create a New Order" << endl;

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    cout << "Available Menu Items:" << endl;
    menuList(); 

    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    Order currentOrder;
    currentOrder.orderId = totalOrders + 1;
    currentOrder.totalItems = 0;
    currentOrder.totalPrice = 0;
    // Initialize all items to 0
    for (int i = 0; i < 5; i++) {
        currentOrder.items[i].itemId = 0;
        currentOrder.items[i].quantity = 0;
    }

    while (true) {
        cout << "Current Order Total: €" << currentOrderTotal << endl;
        cout << "Enter Item ID to add (or 0 to finish order): ";
        cin >> itemId;

        if (itemId == 0) {
            break;
        }

        if (itemId < 1 || itemId > totalMenuItems) {
            cout << "Invalid item ID. Please try again." << endl;
            continue;
        }

        addItemsToOrder(itemId, currentOrderTotal, currentOrder, totalItems, currentOrderItems);
    }
}

// Adding items to the order
void addItemsToOrder(int itemId, int& currentOrderTotal, Order& currentOrder, int& totalItems, int&currentOrderItems) {
    string itemName = itemNames[itemId - 1];
    double itemPrice = itemPrices[itemId - 1];

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    cout << "Selected item: " << itemName << " - €" << itemPrice << endl;
    cout << "Enter Quantity: ";

    int quantity;
    cin >> quantity;

    OrderItemDetails currentOrderDetails;
    currentOrderDetails.itemId = itemId; 
    currentOrderDetails.quantity = quantity;

    currentOrder.items[currentOrderItems++] = currentOrderDetails;

    int itemTotal = itemPrice * quantity;
    currentOrderTotal += itemTotal;  
    currentOrder.totalItems += quantity;  
    totalItems += quantity;

    cout << "Added to order: " << itemName << " x" << quantity << " = €" << itemTotal << endl;
    cout << "New Order Total: €" << currentOrderTotal << endl;

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    cout << "1. Add More Items" << endl;
    cout << "2. Finish Order" << endl;
    cout << "3. Cancel Order" << endl;

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            break;

        case 2:
            cout << "Thank you for your order!" << endl;
            cout << "Your final order details are:\n" << endl;

            currentOrder.totalPrice = currentOrderTotal;
            currentOrder.totalItems = totalItems;

            // Debugging: Print out order details to check if it's correctly created
            cout << "Order ID: " << currentOrder.orderId << endl;
            cout << "Total Items: " << currentOrder.totalItems << endl;
            cout << "Total Price: €" << currentOrder.totalPrice << endl;

            // Add the current order to the global orders array
            orders[totalOrders] = currentOrder;
            totalOrders++;  // Increment the total number of orders
            orderTotal += currentOrderTotal;  // Add the current order's total to the overall total
            totalItems += totalItems; // Update the global totalItems with the items from this order

            orderManagement();
            break;

        case 3:
            cout << "\nYour Order has been Cancelled." << endl;
            currentOrderTotal = 0;
            currentOrder.totalItems = 0;  // resets total items if order gets cancelled
            currentOrder.totalPrice = 0; //resets total price
            totalItems = 0; // reset local totalItems
            orderManagement();
            break;

        default:
            cout << "Invalid Choice, please try again." << endl;
            break;
    }
}

//Resetting order Confirmation
void resetOrderConfirmation() {
    int choice;

    while (true) {
        cout << "--------------------------------" << endl;
        cout << "--------------------------------" << endl;

        cout << "\n Final Confirmation" << endl;

        cout << "--------------------------------" << endl;
        cout << "--------------------------------" << endl;

        cout << "Are you sure you want to reset this order?" << endl;
        cout << endl;

        cout << "You are about to delete " << totalOrders << " " << "order/orders" << endl;

        cout << "This action cannot be undone!" << endl; 
        
        cout << "--------------------------------" << endl;

        cout << "1. Yes, reset all orders" << endl; 
        cout << "2. No, I want to cancel" << endl; 

        cout << "--------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice; 

        if (choice == 1) {
            totalOrders = 0;
            orderTotal = 0;
            totalItems = 0;
            cout << "All orders have been reset!" << endl;
            break; // Exit the loop after resetting

        } else if (choice == 2) {
            cout << "Reset cancelled." << endl;
            break; // Exit the loop and return

        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } orderManagement();
}


// Resetting order
void resetOrder() {

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "\n Reset All Orders" << endl;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    orderList();
    cout << endl;

    if (totalOrders == 0) {
        cout << "No orders to reset." << endl;
        return;
    }
    cout << "WARNING: THIS ACTION CANNOT BE UNDONE!" << endl;

    cout << "--------------------------------" << endl;

    cout << " 1. Yes, Reset all orders " << endl;
    cout << " 2. No, go back " << endl;

    cout << "--------------------------------" << endl;

    cout << "Enter your choice: " << endl; 
    int choice; 
    cin >> choice; 

    if (choice == 1) {
        cout << "Resetting all orders..." << endl;
        resetOrderConfirmation(); 
        return;
    }

    if (choice == 2) {
        orderManagement();
        return;
    }

    if (choice < 1 || choice > 2) {
        cout << "Invalid choice, please try again." << endl;
        return;
    }
}

//Order Management Function
void orderManagement() {
    int option;
    do { // Loops to show menu management options until user goes back to the main menu
        cout << "---------------------------------" << endl;
        cout << "---------------------------------" << endl;

        cout << "\n Order Management" << endl;

        cout << "---------------------------------" << endl;
        cout << "---------------------------------" << endl;

        cout << "1. Create new orders" << endl;
        cout << "2. View all orders" << endl;
        cout << "3. Delete Orders" << endl;
        cout << "4. Reset Orders" << endl;
        cout << "5. Back to Main Menu" << endl;

        cout << "---------------------------------" << endl;
        cout << "---------------------------------" << endl;

        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Creating new order..." << endl;
                createNewOrder();  // Call function to create new order
                break;

            case 2:
                cout << "Viewing all orders..." << endl;
                if (viewAllOrders() == 1) {
                    option = 5;
                }
                break;

            case 3:
                cout << "Deleting orders..." << endl;
                deleteOrder();  // Call function to delete orders (you need to implement this function)
                break;

            case 4:
                cout << "Resetting orders..." << endl;
                resetOrder();
                break;

            case 5:
                cout << "Going back to Main Menu..." << endl;
                return; // Exit the loop and return to the main menu

            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (option != 5); // Loops until the user chooses to go back to main menu
}