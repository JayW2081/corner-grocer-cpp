#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H

#include <map>
#include <string>

class GroceryTracker {
public:
    // Reads item data from the input file and stores item frequencies.
    bool LoadItemsFromFile(const std::string& fileName);

    // Writes all item frequencies to frequency.dat for backup.
    bool WriteFrequencyBackup(const std::string& fileName) const;

    // Returns the purchase frequency for one item. The search is case-insensitive.
    int GetItemFrequency(const std::string& itemName) const;

    // Prints every item with its numeric purchase frequency.
    void PrintAllFrequencies() const;

    // Prints every item with a text-based histogram using asterisks.
    void PrintHistogram() const;

private:
    std::map<std::string, int> m_itemFrequencies;

    // Converts user input to a consistent format for reliable searching.
    static std::string NormalizeItemName(const std::string& itemName);
};

#endif
