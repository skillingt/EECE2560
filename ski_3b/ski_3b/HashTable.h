//
//  HashTable.h
//  ski_3b
//
//  Created by Taylor Skilling on 10/18/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//

#ifndef __ski_3b__HashTable__
#define __ski_3b__HashTable__

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class HashTable
{
private:
    vector<vector<T>> table;
    // Want to find a prime number between two power of two that satisfies ~3 collisions (90,000/3)
    // 90,000 / 3 = 30,000
    // 2^15 = 32768 2^14 = 16384
    // Prime Number: 20,947
    int table_length = 20947;
public:
    HashTable(); // Constructor
    void AddItem(T &item); // Add an item to the hash table
    void DeleteItem(T &item); // Delete an item from the hash table
    bool InList(T &item); // Searches for an item in the table, returns true if found
    int Hash(T &item); // Returns the hash value for an item
    bool Search(T &item); // Calls the InList function, used as a work around in the FindMatches
};

// Constructor
template <typename T>
HashTable<T>::HashTable(){
    // Initialize the Hash Table to the table length
    table.resize(table_length);
}

// Hash function
template <typename T>
int HashTable<T>::Hash(T &item)
{
    hash<T> h; // specializes h() to work on obj type T
    return h(item) % table_length;
}

// Add Item
template <typename T>
void HashTable<T>:: AddItem(T &item)
{
    int index = Hash(item);
    table.at(index).push_back(item);
}

// Delete Item
template <typename T>
void HashTable<T>:: DeleteItem(T &item) {
    // Find the item
    int index = Hash(item);
    // Loop over the key vector
    for (int i = 0; i < table.at(index).size(); i++) {
        // Find the index in which the item resides
        if (table.at(index).at(i) == item) {
            // Delete the item
            table.at(index).erase(table.at(index).begin()+i);
        }
    }
}

// Searches for an item in the table, returns true if found
template <typename T>
bool HashTable<T>:: InList(T &item) {
    // Find the item
    int index = Hash(item);
    // Loop over the key vector
    for (int i = 0; i < table.at(index).size(); i++) {
        // Find the index in which the item resides
        if (table.at(index).at(i) == item) {
            // Return True
            return true;
        }
    }
    // Item doesn't reside in the key vector, doesn't exist, return false
    return false;
}

template <typename T>
bool HashTable<T>::Search(T &item)
{
    bool result;
    result = InList(item);
    return result;
}

#endif /* defined(__ski_3b__HashTable__) */
