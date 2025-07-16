#include <iostream>
#include <string>
using namespace std;


int viewMenu(); 
int updateMenuItem(); 
void menuManagement();
void orderManagement();
void menuList();


// Structure to hold order details
struct Order {
    int orderId;
    int itemId;  // itemId to store the menu item associated with the order
    int totalItems;       
    double totalPrice;     
};

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




// Making order list global variable to use for view all orders function
void orderList() {
    int totalItems;
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



//confirmation for deleting menu item 
int deleteItemConfirmation(int index){
    int choice;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "\n Confirm Deletetion" << endl;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "Are you sure you want to delete this item?" << endl;
    cout << "Item Name: " << itemNames[index] << endl;
    cout << "Item Price: €" << itemPrices[index] << endl;

    cout << "This action cannot be undone!" << endl; 

    cout << "--------------------------------" << endl;

    cout << "1. Yes, I want to delete this item" << endl; 
    cout << "2. No, I want to cancel" << endl; 

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "Enter your choice: ";
    cin >> choice; 

    if (choice == 1) {
        for (int i = index; i < totalMenuItems - 1; i++) {
            itemNames[i] = itemNames[i+1]; //shifts the menu items so the deleted item is removed
            itemPrices[i] = itemPrices[i+1]; 
        }
        totalMenuItems--; //decreases the total menu items by 1

        cout << " Your item has been successfully deleted!" << endl; 

    } else if (choice == 2) {
        cout << "Item deletion is cancelled." << endl;
        return 0; 
    
    }  else {
        cout << "Invalid choice. Please try again." << endl;
        return deleteItemConfirmation(index);
    }

    return 0;
}




// Delete Menu Item
int deleteMenuItem(){
    int itemId;
    int index = itemId - 1; //so the index starts from 0

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "\n Delete Menu Item" << endl;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    menuList();
    cout << endl;

    cout << "WARNING: THIS ACTION CANNOT BE UNDONE!" << endl;
    cout << "Enter Item Id to delete (or 0 to go back): " << endl;

    cin >> itemId;

    if (itemId == 0) {
        cout << "Going back to Menu Management..." << endl;
        return 0;
    }

    if (itemId < 1 || itemId > totalMenuItems) {
        cout << "Invalid item Id, please try again." << endl;
        return deleteMenuItem();
    }

    return deleteItemConfirmation(index);
}




// Add New Menu Item
void addMenuItem(){
    int choice;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "\n Add New Menu Item" << endl;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    if (totalMenuItems == 50) {
        cout << "Menu is full. Cannot add more items." << endl;
        return;
    } else {
        cout << "Please enter the name of the new menu item." << endl;
        cout << "Item Name: ";

        string itemName;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clears the input buffer 
        getline(cin, itemName); // gets the item name from user input

        cout << endl;

        cout << "Please enter the price of the new menu item." << endl; 
        cout << "Item Price: ";

        double itemPrice;
        cin >> itemPrice; // gets the item price from user input

        cout << "--------------------------------" << endl;
        cout << "--------------------------------" << endl;

        cout << "1. Save Item" << endl;
        cout << "2. Cancel and Go Back" << endl;

        cout << "--------------------------------" << endl;
        cout << "--------------------------------" << endl;

        cout << "Enter your choice: ";
        cin >> choice;  

        switch (choice) {
            case 1: 
                itemNames[totalMenuItems] = itemName; 
                itemPrices[totalMenuItems++] = itemPrice;
                cout << "Item: " << itemName << "," << "Price: "<< itemPrice << "€" << " Has Been Added Successfully!" << endl;

                 cout << "\nUpdated Menu:\n";
                 viewMenu();
                break;

            case 2:
                cout << "Going back to Menu Management..." << endl; 
            return; // returns to the calling function (menuManagement)

            default:
                cout << "Invalid option. Please try again." << endl;
            return;

        }
    }
}



// Menu List 
void menuList() {

    cout << "ID \t| Item Name, Price" << endl;
    cout << "--------------------------" << endl;

    for (int i = 0; i < totalMenuItems; i++) { //loops the menu items to desplay them 
        cout << (i + 1) << "  \t| " << itemNames[i];
        if (itemPrices[i] > 0) {
            cout << ", €" << itemPrices[i] << endl; //adds the item price to the menu list 
        } else {
            cout << endl;
        }
    }

    cout << "-----------------------------" << endl;
    cout << "Total Menu Items: " << totalMenuItems << endl;
    cout << "-----------------------------" << endl;
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

    orderManagement();
}



// Viewing total number of orders
void viewAllOrders() {
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
            return;

        case 3:
            return ;

        default:
            cout << "Invalid choice, please try again. " << endl; 
            break;
        }

    } while (choice != 3);
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

    if (orderId < 1 || orderId > totalMenuItems) {
        cout << "Invalid item Id, please try again." << endl;
        return;
    }
    int index = orderId - 1; //so the index starts from 0

    return deleteOrderConfirmation(index);
}



// Adding items to the order 
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
    currentOrderTotal += itemTotal;  // Update the order total
    currentOrder.totalItems += quantity;  // Update total items in the current order

 

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

            // Debugging: Print out order details to check if it's correctly created
            cout << "Order ID: " << currentOrder.orderId << endl;
            cout << "Total Items: " << currentOrder.totalItems << endl;
            cout << "Total Price: €" << currentOrder.totalPrice << endl;

            // Add the current order to the global orders array
            orders[totalOrders] = currentOrder;  
            totalOrders++;  // Increment the total number of orders
            orderTotal += currentOrderTotal;  // Add the current order's total to the overall total

            orderManagement();
            break;

        case 3:
            cout << "\nYour Order has been Cancelled." << endl;
            currentOrderTotal = 0;
            currentOrder.totalItems = 0;  // resets total items if order gets cancelled
            currentOrder.totalPrice = 0; //resets total price
            orderManagement();
            break;

        default:
            cout << "Invalid Choice, please try again." << endl;
            break;
    }
}


//Creating new order
void createNewOrder() {
    int itemId;
    int currentOrderTotal = 0; // Tracks the current order's total price
    int totalItems = 0;        // Tracks the total number of items in the order

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    cout << "\n Create a New Order" << endl;

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    cout << "Available Menu Items:" << endl;
    menuList();  // Display the available menu items
    
    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

    // Initialize a new order
    Order currentOrder;
    currentOrder.orderId = totalOrders + 1;  // Setting order ID (incremental)

    while (true) {
        cout << "Current Order Total: €" << currentOrderTotal << endl;
        cout << "Enter Item ID to add (or 0 to finish order): ";
        cin >> itemId;

        // If user presses 0, finalize the order and exit the loop
        if (itemId == 0) {
            
            break;  // Exit the loop to prevent further input after finishing the order
        }

        // Validation: if itemId is invalid (out of bounds)
        if (itemId < 1 || itemId > totalMenuItems) {
            cout << "Invalid item ID. Please try again." << endl;
            continue;  // Ask for a valid item ID
        }

        // If itemId is valid, add the item to the order
        addItemsToOrder(itemId, currentOrderTotal, currentOrder, totalItems);
    }
}







// Function to display the menu
int viewMenu() { //view menu function 
    int option;
    
    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;
    cout << "\n View Menu Items" << endl;
    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;
    
    menuList(); //calls the menuList function to display the menu items
    
    cout << "-----------------------------" << endl;
    cout << "1. Back to Menu Management" << endl;
    cout << "2. Back to Main Menu" << endl;
    cout << "-----------------" << endl;
    cout << "-----------------" << endl;    

    cout << "Enter your choice: ";
    cin >> option;

    switch (option) {
        case 1:
            cout << "Returning to Menu Management..." << endl;
            return 0; // returns to the calling function (menuManagement)
        case 2:
            cout << "Returning to Main Menu" << endl;
            return 1; //goes back to the main menu
    }
    return 1;
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
                viewAllOrders();  // Call function to view all orders
                break;

            case 3:
                cout << "Deleting orders..." << endl;
                deleteOrder();  // Call function to delete orders (you need to implement this function)
                break;

            case 4:
                cout << "Resetting orders..." << endl;
                break;

            case 5:
                cout << "Going back to Main Menu..." << endl;
                return; // Exit the loop and return to the main menu

            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (option != 5); // Loops until the user chooses to go back to main menu
}





//Menu Management Function
void menuManagement() { 
    int option;
    do { //loops to show menu management options until user goes back to main menu

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

     cout << "\n Menu Management" << endl;

    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;

        cout << "1. View Menu Items" << endl;
        cout << "2. Add Menu Item" << endl;
        cout << "3. Update Menu Item" << endl;
        cout << "4. Delete Menu Item" << endl;
        cout << "5. Back to Main Menu" << endl;


        cout << "Enter your choice: ";
        cin >> option;


        switch (option) {
            case 1:
                cout << "Viewing menu items..." << endl;
                if (viewMenu() == 1){
                    option = 5; //exits menuMangement function and returns to main menu
                }
                break; //stops the excution of switch statementi if case 1 is selected

            case 2:
                cout << "Adding a new menu item..." << endl;
                addMenuItem();
                break; //stops the excution of switch statementi if case 2 is selected
            
            case 3:
                cout << "Updating a menu item..." << endl;
                updateMenuItem();
                break; //stops the excution of switch statementi if case 3 is selected
            
            case 4:
                cout << "Deleting a menu item..." << endl;
                deleteMenuItem();
                break; //stops the excution of switch statementi if case 4 is selected  
           
            case 5:
                cout << "Returning to Main Menu..." << endl;
                break; //stops the excution of switch statementi if case 5 is selected
           
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } 
    while (option != 5); // loops until the user chooses to go back to main menu 
}                  


//Confirmation for updating menu item
int updateConfirmation(int index){
    int choice;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "Confirm Updates" << endl;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "Old Details: " << endl; 
    cout << "Item name: " << itemNames[index] << endl; //index[0] is a placeholder for first item in menu 
    cout << "item Price: €" << itemPrices[index] << endl;

    cout << endl;

    cout << "New Details: " << endl;
    cout << "Item Name: " << itemNames[index] << endl;
    cout << "Item Price: €" << itemPrices[index] << endl; 
    
    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << " 1. Confirm changes" << endl;
    cout << " 2. Cancel" << endl;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;


    cout << "Enter your choice: ";
    cin >> choice; 

    if (choice == 1) {
        cout << "Changes have successfully been made!" << endl;
        return 0; //returns to updateMenuItem ()

    } else if (choice == 2) {
        cout << "Changes have been cancelled." << endl;
        return 0; //returns to updateMenuItem()
    } else {
        cout << "Invalid choice. Please try again." << endl;
        return updateConfirmation(index); //calls this function again till a valid choice is made by the user 

    }
}
   



// Update Menu Item 
int updateMenuItem(){
    int itemID;
    int choice;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "\n Update Menu Items" << endl; 

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

   menuList(); //calls the menuList function to display the menu items
    

    cout << "Enter item ID to update (or 0 to go back): ";
    cin >> itemID;

    if (itemID == 0) {
        cout << "Going back to Menu Management..." << endl;
        return 0;
    }

    if (itemID < 1 || itemID > totalMenuItems) {
        cout << "Invalid item ID, please try again." << endl;
        return 0;
    }

    int index = itemID - 1;

    cout << "Current Details: " << endl; 
    cout << "Item name: " << itemNames[index] << endl;
    cout << "Item price: €" << itemPrices[index] << endl;

    cout << "--------------------------------" << endl;

    cout << "Enter New Details" << endl;
    cout << "New item name: ";

    cin >> itemNames[index];

    cout << "New item price: ";
    cin >> itemPrices[index];

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << " 1. Save Changes" << endl;
    cout <<" 2. Cancel" << endl;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    if (itemID == 0) {
        cout << "Going back to Menu Management..." << endl;
        return 0;
    }

    if (itemID < 1 || itemID > totalMenuItems) {
        cout << "Invalid item ID, please try again." << endl;
        return 0;
    }
    return updateConfirmation(index); //calls the updateConfirmation function to confirm the updates
}



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
