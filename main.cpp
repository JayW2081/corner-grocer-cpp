#include "GroceryTracker.h"

#include <iostream>
#include <limits>
#include <string>

using namespace std;

void PrintMenu() {
    cout << "\nCorner Grocer Item Tracking Program" << endl;
    cout << "-----------------------------------" << endl;
    cout << "1. Search for an item frequency" << endl;
    cout << "2. Print all item frequencies" << endl;
    cout << "3. Print item frequency histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int GetMenuChoice() {
    int choice;

    while (!(cin >> choice) || choice < 1 || choice > 4) {
        cout << "Invalid menu option. Please enter 1, 2, 3, or 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int main() {
    const string inputFileName = "CS210_Project_Three_Input_File.txt";
    const string backupFileName = "frequency.dat";

    GroceryTracker tracker;

    if (!tracker.LoadItemsFromFile(inputFileName)) {
        cout << "Error: Could not open " << inputFileName << "." << endl;
        cout << "Make sure the input file is in the same folder as the program." << endl;
        return 1;
    }

    if (!tracker.WriteFrequencyBackup(backupFileName)) {
        cout << "Error: Could not create " << backupFileName << "." << endl;
        return 1;
    }

    bool keepRunning = true;

    while (keepRunning) {
        PrintMenu();
        int choice = GetMenuChoice();

        switch (choice) {
        case 1: {
            string itemName;
            cout << "Enter the item you wish to search for: ";
            getline(cin, itemName);

            cout << itemName << " was purchased "
                 << tracker.GetItemFrequency(itemName) << " time(s)." << endl;
            break;
        }
        case 2:
            tracker.PrintAllFrequencies();
            break;
        case 3:
            tracker.PrintHistogram();
            break;
        case 4:
            cout << "Thank you for using the Corner Grocer tracking program." << endl;
            keepRunning = false;
            break;
        default:
            // This should not occur because GetMenuChoice validates the input.
            cout << "Invalid selection." << endl;
            break;
        }
    }

    return 0;
}
