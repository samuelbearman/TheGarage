/*
 * Name: Samuel Bearman
 * File: Project1 CMSC 202, Fall 2017
 * Date: 9/25/17
 * Section: 14
 * Email: bearman1@umbc.edu
 *
 * Description: This program simulates a food selection station where user can select 
 * certain foods to order. Calculates Tax and allows for selection of quantity.
 *
 * */



#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

#define MAX_SIZE 10 // Used to define size of arrays for holding file information of price and type of food

using namespace std;


/*
 * These are the all the prototypes for the functions degined for the program, each one has an individual 
 * description above where they are written below
 *
 * */


int mainMenu();
bool verifySelect(int selection);
void loadArray( string foodArry[], string priceArry[]);
void showMenu( string foodArry[], string priceArry[]);
bool moreItems();
int inputItem();
int inputQuantity();
void showReciept( int Item[], int Quantity[],string foodArry[], string priceArry[], int orderLength);
void lastReciept();




int main() {

    
    string foodArry[MAX_SIZE];      // Array for storing all the food names
    
    string priceArry[MAX_SIZE];     // Array for storing all the prices of the food
    

    
    int menuSelect = 0;             // used for taking in user input during the menu select
    
    bool menuRun = true;            // boolean for establishing if the program should continue running
    
    bool selectRun = true;          // boolean used in selection of orders 

    while(menuRun == true) {
    // Label made for user error in menu selection
    beginning:
        // uses function to take in user input at main menu
        menuSelect = mainMenu();
        // takes variable "menuSelect" and verifies if it's a good selection
        menuRun = verifySelect(menuSelect); 
        if (menuRun == false) {
	    // If the function returns back false, then go back and try user input again
            goto beginning; 
        }

        switch(menuSelect) {
   	        // For the case of a "New Order"
            case 1: 
                {
		    
                    int Items[10];          // Used to hold the items that the user actuall selected
		    
                    int Quantity[10];       // Used to hold the prices of the food that the user selected
 		    
                    int orderLength = 0;    // Integer use to hold how many orders the user has so far
 		    
                    selectRun = true;       // boolean used to establish if the user is stil putting in orders or not

 		            // function loads the food and price file into arrays
                    loadArray(foodArry, priceArry);
 		            // function shows current food and price menu
                    showMenu(foodArry, priceArry); 
                    while(selectRun == true) {
			        // Asks for users order
                        Items[orderLength] = inputItem();
 			            // Asks for users quantity of order
                        Quantity[orderLength] = inputQuantity(); 
                        // Checks to see if the user has maxed out on possible number of orders, if they have already ordered 3 then the program
                        // will no longer ask if they want another order and will go straight to checkout
			            if(orderLength < 2) {   
                            selectRun = moreItems();
                        } else {
                            selectRun = false;
                        }     
                        // Adds to the current number of orders
			            orderLength++; 
                    } 
                    showReciept(Items, Quantity, foodArry, priceArry, orderLength); // Function writes out to user and to text file what their reciept is 
                    break;
                }
    
	        // For the case of "Show Last Reciept
            case 2:
 	        // Function that will show the last reciept that was written
                lastReciept();
 	        // For the case of "Exit"
            case 3: 
                cout << "Exiting Program" << endl; 
                // terminates while loop and exits program
		        menuRun = false; 
        }
    }
    return 0;
}


// moreItems
// Function that assigns user input to int variable asking if they would like to order more than one item

bool moreItems() {

    bool valid = true;
    char yesNo;

    while(valid != false) {
        cout << "Would you like to order more items? (y/n)?" << endl;
        cin >> yesNo;
        
        if(yesNo == 'y') {
            return true;
        } else if(yesNo == 'n') {
            return false;
        } else {
            continue;
        }
    }
}


// inputItems
// Function that takes user input asking what they would like to order, returns an int. 

int inputItem() {

    int item;
    bool valid = true;
    while(valid != false) {
        int item = 0;
        cout << "What would you like to order? " << endl;
        cin >> item;
        // Used to see if user inputed a value higher than 10 or lower than 0
        if(item > 10 || item < 0) {
            valid = true;
        } else {
            // Since item is used as an index and since 0 is not on the list of selectable food options, we increment down
            item = item - 1;
            return item;
        }
    }
}


// inputQuantity
// FUnction that takes user input asking how much they would like to order of a specific item, returns an int

int inputQuantity() {

    int quantity = 0;
    bool valid = true;
    while(valid != false) {
        int quantity = 0;
        cout << "How many would you like to buy?" << endl;
        cin >> quantity;
        // Checks that user didnt input higher than 10 or lower than 0
        if(quantity > 10 || quantity < 0) {
            valid = true;
        } else {
            return quantity;
        }
    }
}


// mainMenu()
// This function is teh main menu selection screen, It is designed to be able to easily be reused
// for re-prompting the user. It returns the selection the user picked but does not verify it,
// this is done in the function it is put in as a parameter.

int mainMenu() {
    int selection = 0;
    cout << "Hello and welcome to True Grit. Please select an option below " << endl;
    cout << "1. New order " << endl;
    cout << "2. Last receipt " << endl;
    cout << "3. Exit " << endl;

    cin >> selection;
    return selection;
}


// verifySelect
// This function takes in the variable from mainMenu and verifies if it is a possible selection
// (1-3) and returns a boolean value for if it was a good variable or not. If it is not the the while
// loop in main is broken.

bool verifySelect(int selection) {
    bool isVerified;
    
    switch(selection) {
        case 1:
            isVerified = true;
            break;
        case 2:
            isVerified = true;
            break;
        case 3:
            isVerified = true;
            break;
        default:
            isVerified = false;
            break;
    }

    return isVerified;
}



// loadArray
// This function takes in the two arrays foodArry and priceArry and loads them with the info 
// from the text file "proj1_items.txt". These arrays are used to reference food and prices 
// for calculating user costs and quantity. This now utilizes "getline" in order to have multi word
// food names.

void loadArray( string foodArry[], string priceArry[]) {
    string currentFood = " ";
    string currentPrice = " ";
    int counter = 0;

    string currentLine = " ";

    ifstream inputStream("proj1_items.txt");

    //While loop gets each piece of data from the file, stores in variables depending on the type of data
    while (getline(inputStream, currentFood, ',')) {
        foodArry[counter] = currentFood;
        getline(inputStream, currentPrice);
        priceArry[counter] = currentPrice;
        counter++;
    }     
    inputStream.close(); 

}


// showMenu
// After the user has selected that they would like to have a new order, this function displays the possible 
// food selection in a nice menu screen.
void showMenu( string foodArry[], string priceArry[]) {

    int currentNumber = 0;
    double calcDouble;
    

    cout << "Number             Item                  Price" << endl;
    for( currentNumber = 0; currentNumber < 10; currentNumber++) {
        // Used to convert string to double for nice output below
        stringstream ss;
        ss << priceArry[currentNumber];
        ss >> calcDouble;
        // output setup to make nice looking menu
        cout  << setw(4) << currentNumber + 1 << "." << setw(25) << foodArry[currentNumber] << setw(12) << "$" << fixed << setprecision(2) << calcDouble << endl;
    }

}


// showReciept (rename to "makeReciept")
// Takes in all the necessary information to show the output of a reciept, shows in a nice format, and also writes to the 
// "proj1_recipt.txt" file.


void showReciept( int Item[], int Quantity[], string foodArry[], string priceArry[], int orderLength) {

    int currentNumber = 0;
    double calcDouble;
    double runningTotal;
    double taxedTotal;

    remove("proj1_reciept.txt");
    ofstream outfile("proj1_reciept.txt");

    cout << "Below is your reciept" << endl;
    cout << "Qnty               Item                 Price" << endl;
    outfile << "Qnty               Item                 Price" <<endl;  

    for( currentNumber = 0; currentNumber < orderLength; currentNumber++) {
        stringstream ss;
        ss << priceArry[Item[currentNumber]];
        ss >> calcDouble;
        // Output format to screen 
        cout << setw(4) <<  Quantity[currentNumber] << setw(25) << foodArry[Item[currentNumber]] << setw(12) << "$" << fixed << setprecision(2) << calcDouble << endl;
        // Output to file 
        outfile << setw(4) << Quantity[currentNumber] << setw(25) << foodArry[Item[currentNumber]] << setw(12) << "$" << fixed << setprecision(2) << calcDouble << endl;
        runningTotal += calcDouble;
    }
    // Calculations done for tax and totals
    taxedTotal = runningTotal + (runningTotal * .06);

    cout << "Subtotal: " << runningTotal << endl;
    outfile << "Subtotal: " << runningTotal << endl;
    cout << "Tax: " << runningTotal * .06 << endl;
    outfile << "Tax: " << runningTotal * .06 << endl;
    cout << "Total: " << taxedTotal << endl;
    outfile << "Total: " << taxedTotal << endl;

    cout << "Reciept was written" << endl;
    outfile.close();


}


// lastReciept
// Function that takes in the data from "proj1_reciept.txt" and outputs it to the screen

void lastReciept() {
   
    string content;
    ifstream readFile("proj1_reciept.txt");

    while(! readFile.eof()) {
        getline(readFile, content);
        cout << content <<endl;
    }
    readFile.close();
}

