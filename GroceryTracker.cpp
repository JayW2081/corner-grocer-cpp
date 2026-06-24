#include "GroceryTracker.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>

using namespace std;

bool GroceryTracker::LoadItemsFromFile(const string& fileName) {
    ifstream inputFile(fileName);
    string itemName;

    if (!inputFile.is_open()) {
        return false;
    }

    // Read each item from the file and count how many times it appears.
    while (inputFile >> itemName) {
        m_itemFrequencies[NormalizeItemName(itemName)]++;
    }

    inputFile.close();
    return true;
}

bool GroceryTracker::WriteFrequencyBackup(const string& fileName) const {
    ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        return false;
    }

    // Write accumulated frequency data to a backup file.
    for (const auto& item : m_itemFrequencies) {
        outputFile << item.first << " " << item.second << endl;
    }

    outputFile.close();
    return true;
}

int GroceryTracker::GetItemFrequency(const string& itemName) const {
    string normalizedItem = NormalizeItemName(itemName);
    auto itemIterator = m_itemFrequencies.find(normalizedItem);

    if (itemIterator != m_itemFrequencies.end()) {
        return itemIterator->second;
    }

    return 0;
}

void GroceryTracker::PrintAllFrequencies() const {
    cout << "\nItem Purchase Frequencies" << endl;
    cout << "-------------------------" << endl;

    for (const auto& item : m_itemFrequencies) {
        cout << item.first << " " << item.second << endl;
    }
}

void GroceryTracker::PrintHistogram() const {
    cout << "\nItem Purchase Histogram" << endl;
    cout << "-----------------------" << endl;

    for (const auto& item : m_itemFrequencies) {
        cout << item.first << " ";

        for (int i = 0; i < item.second; ++i) {
            cout << "*";
        }

        cout << endl;
    }
}

string GroceryTracker::NormalizeItemName(const string& itemName) {
    string normalizedItem = itemName;

    if (normalizedItem.empty()) {
        return normalizedItem;
    }

    // Make the comparison case-insensitive while keeping output clean.
    transform(normalizedItem.begin(), normalizedItem.end(), normalizedItem.begin(),
              [](unsigned char character) { return static_cast<char>(tolower(character)); });

    normalizedItem[0] = static_cast<char>(toupper(normalizedItem[0]));

    return normalizedItem;
}
