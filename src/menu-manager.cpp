#include <iostream>
#include <string>
#include <limits>
using namespace std;

//global vars
extern string itemNames[50];
extern double itemPrices[50];
extern int totalMenuItems;

//func declaration
int viewMenu(); 
int updateMenuItem(); 
void menuManagement();
void menuList();
int deleteMenuItem();
int deleteItemConfirmation(int index);
void addMenuItem();
int updateConfirmation(int index);

void menuList() {

    cout << "ID \t| Item Name, Price" << endl;
    cout << "--------------------------" << endl;

    for (int i = 0; i < totalMenuItems; i++) { //display all menu items 
        cout << (i + 1) << "  \t| " << itemNames[i];
        if (itemPrices[i] > 0) {
            cout << ", €" << itemPrices[i] << endl; 
        } else {
            cout << endl;
        }
    }

    cout << "-----------------------------" << endl;
    cout << "Total Menu Items: " << totalMenuItems << endl;
    cout << "-----------------------------" << endl;
}

int viewMenu() {  
    int option;
    
    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;
    cout << "\n View Menu Items" << endl;
    cout << "---------------------------------" << endl;
    cout << "---------------------------------" << endl;
    
    menuList(); //displays all menu items
    
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
            return 0; //return to menu management
        case 2:
            cout << "Returning to Main Menu" << endl;
            return 1; //return to main menu
    }
    return 1;
}

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
        getline(cin, itemName); //get the item name from user

        cout << endl;

        cout << "Please enter the price of the new menu item." << endl; 
        cout << "Item Price: ";

        double itemPrice;
        cin >> itemPrice; // get the item price from user 

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
            return; //return to menu management

            default:
                cout << "Invalid option. Please try again." << endl;
            return;

        }
    }
}

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
            itemNames[i] = itemNames[i+1]; //shift items to remove deleted menu item
            itemPrices[i] = itemPrices[i+1]; 
        }
        totalMenuItems--; 

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

int deleteMenuItem(){
    int itemId;
    int index = itemId - 1; 

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

int updateConfirmation(int index){
    int choice;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "Confirm Updates" << endl;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "Old Details: " << endl; 
    cout << "Item name: " << itemNames[index] << endl; 
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
        return 0; //return to updateMenuItem ()

    } else if (choice == 2) {
        cout << "Changes have been cancelled." << endl;
        return 0; // return to updateMenuItem()
    } else {
        cout << "Invalid choice. Please try again." << endl;
        return updateConfirmation(index); //call until valid chaoice by user

    }
}

int updateMenuItem(){
    int itemID;
    int choice;

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

    cout << "\n Update Menu Items" << endl; 

    cout << "--------------------------------" << endl;
    cout << "--------------------------------" << endl;

   menuList(); //display menu items
    

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
    return updateConfirmation(index); //to confirm the updates
}

void menuManagement() { 
    int option;
    do { 

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
                    option = 5; //return to main menu
                }
                break; 

            case 2:
                cout << "Adding a new menu item..." << endl;
                addMenuItem();
                break; 
            
            case 3:
                cout << "Updating a menu item..." << endl;
                updateMenuItem();
                break; 
            
            case 4:
                cout << "Deleting a menu item..." << endl;
                deleteMenuItem();
                break; 
           
            case 5:
                cout << "Returning to Main Menu..." << endl;
                break; 
           
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } 
    while (option != 5); 
}                  
