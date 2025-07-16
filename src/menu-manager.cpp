#include <iostream>
#include <string>
#include <limits>
using namespace std;

// External global variables (defined in utils.cpp)
extern string itemNames[50];
extern double itemPrices[50];
extern int totalMenuItems;

// Function declarations
int viewMenu(); 
int updateMenuItem(); 
void menuManagement();
void menuList();
int deleteMenuItem();
int deleteItemConfirmation(int index);
void addMenuItem();
int updateConfirmation(int index);

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
    cout << " 2. Cancel" << endl;

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
