#include <iostream>
#include <string>
using namespace std;

struct Order;

//global vars
extern Order orders[50];
extern int totalOrders;
extern int orderTotal;
extern string itemNames[50];
extern double itemPrices[50];
extern int totalMenuItems;

extern void menuList();

// Fn declaration
void orderList();
void viewOrderDetails();
void deleteOrder();
void deleteOrderConfirmation(int index);
int viewAllOrders();
void createNewOrder();
void addItemsToOrder(int itemId, int& currentOrderTotal, Order& currentOrder, int& totalItems);
void orderManagement();
void resetOrder(); 
void resetOrderConfirmation();

void orderList() {
    cout << " -------------------------------------" << endl;
    cout << "| Order ID | Total Items | Total Price " << endl;
    cout << " -------------------------------------" << endl;

    for (int i = 0; i < totalOrders; i++) {
        printf("| %-8d | %-11d | €%10.2f\n", 
               orders[i].orderId, 
               orders[i].totalItems, 
               orders[i].totalPrice);
    }

    cout << "--------------------------------------" << endl;
    cout << "Total Orders: " << totalOrders << endl;
    cout << "Total Order Amount: €" << orderTotal << endl;
    cout << "--------------------------------------" << endl;
}

void viewOrderDetails() {
    int orderId;

    cout << "-----------------------------" << endl;
    cout << "Enter Order ID to view details: ";
    cin >> orderId;

    if (orderId < 1 || orderId > totalOrders) {  // order id shld be valid
        cout << "Invalid Order ID. Please try again." << endl;
        return;  
    }

    cout << "Order ID: " << orders[orderId - 1].orderId << endl;  
    cout << "Total Items: " << orders[orderId - 1].totalItems << endl;
    cout << "Total Price: €" << orders[orderId - 1].totalPrice << endl;

    orderManagement();
}

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
            //subtract the deleted orders price 
            orderTotal -= orders[index].totalPrice;
            for (int i = index; i < totalOrders - 1; i++) { 
                orders[i] = orders[i + 1];
            }
            totalOrders--;

            cout << "Your order has been successfully deleted!" << endl;
            break; //to go back to order management
        } else if (choice == 2) {
            cout << "Order deletion is cancelled." << endl;
            break; //to go back to order management
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    orderManagement();
}

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

    if (orderId < 1 || orderId > totalMenuItems) {
        cout << "Invalid item Id, please try again." << endl;
        return;
    }
    int index = orderId - 1; //making sure the ind starts from 0

    return deleteOrderConfirmation(index);
}

void createNewOrder() {
    int itemId;
    int currentOrderTotal = 0; 
    int totalItems = 0;        

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    cout << "\n Create a New Order" << endl;

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    cout << "Available Menu Items:" << endl;
    menuList();  //to show the available menu itmes

    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    //create a new order
    Order currentOrder;
    currentOrder.orderId = totalOrders + 1;  

    while (true) {
        cout << "Current Order Total: €" << currentOrderTotal << endl;
        cout << "Enter Item ID to add (or 0 to finish order): ";
        cin >> itemId;

        if (itemId == 0) {

            break;  //exit after finishing the order
        }

        //making sure item id is valid 
        if (itemId < 1 || itemId > totalMenuItems) {
            cout << "Invalid item ID. Please try again." << endl;
            continue;  
        }

        addItemsToOrder(itemId, currentOrderTotal, currentOrder, totalItems);
    }
}

void addItemsToOrder(int itemId, int& currentOrderTotal, Order& currentOrder, int& totalItems) {

    string itemName = itemNames[itemId - 1];
    double itemPrice = itemPrices[itemId - 1];

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    cout << "Selected item: " << itemName << " - €" << itemPrice << endl;
    cout << "Enter Quantity: ";

    int quantity;
    cin >> quantity;

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
            return; //will continue to add items

        case 2:
            cout << "Thank you for your order!" << endl;
            cout << "Your final order details are:\n" << endl;

            currentOrder.totalPrice = currentOrderTotal;
            currentOrder.totalItems = totalItems;

            cout << "Order ID: " << currentOrder.orderId << endl;
            cout << "Total Items: " << currentOrder.totalItems << endl;
            cout << "Total Price: €" << currentOrder.totalPrice << endl;

            //add curr order to orders array
            orders[totalOrders] = currentOrder;
            totalOrders++;  
            orderTotal += currentOrderTotal;  
            totalItems += totalItems; 

            orderManagement();
            break;

        case 3:
            cout << "\nYour Order has been Cancelled." << endl;
            currentOrderTotal = 0;
            currentOrder.totalItems = 0;  //reset total items if order gets cancelled
            currentOrder.totalPrice = 0; //reset total price
            totalItems = 0; // reset totalItems
            orderManagement();
            break;

        default:
            cout << "Invalid Choice, please try again." << endl;
            break;
    }
}

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
            break; //exit after resetting 

        } else if (choice == 2) {
            cout << "Reset cancelled." << endl;
            break; 

        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } orderManagement();
}


void resetOrder(){

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

void orderManagement() {
    int option;
    do { 
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
                createNewOrder();  //function to create new order
                break;

            case 2:
                cout << "Viewing all orders..." << endl;
                if (viewAllOrders() == 1) {
                    option = 5;
                }
                break;

            case 3:
                cout << "Deleting orders..." << endl;
                deleteOrder();  //function to delete orders
                break;

            case 4:
                cout << "Resetting orders..." << endl;
                resetOrder();
                break;

            case 5:
                cout << "Going back to Main Menu..." << endl;
                return; 

            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (option != 5); //Loop until the user chooses to go back to main menu
}