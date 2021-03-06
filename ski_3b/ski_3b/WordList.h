//
//  WordList.h
//  ski_3b
//
//  Created by Taylor Skilling on 10/18/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Stores the word list in a vector, and which includes:
// (a) a function to read the words from the wordlist file
// (b) an overloaded output operator to print the word list
// (c) functions that sort the words using 1) insertionsort, 2) quicksort, and 3) mergesort
// (d) a function to handle word lookups using binary search

#ifndef __ski_3b__WordList__
#define __ski_3b__WordList__

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Heap.h"

using namespace std;

class WordList
{
private:
    vector<string> word_list;
public:
    // WordList(); // Constructor
    // WordList(const WordList &);// Copy Constructor
    // WordList& operator= (const WordList &); // Overloaded Assignment Operator
    // ~WordList (){}; // Destructor
    friend ostream& operator<<(ostream& os, const WordList& list); // Overloaded output operator
    vector<string> GetList(); // Getter for the word list
    void ReadWords(); // Read words from the word list file and store it in the list vector
    void InsertionSort(); // Insertion Sort
    void Merge(int l, int m, int r); // Merge
    void MergeSort(int l, int r); // Merge Sort
    int Partition (int l, int h); // Partition
    void QuickSort(int l, int h); // Quick Sort
    void HeapSort(); // Heap Sort
    bool BinarySearch(string key); // Binary Search
    bool Search(string key); // Wrapper for Binary Search
};


#endif /* defined(__ski_3b__WordList__) */
