//
//  WordList.cpp
//  ski_3a
//
//  Created by Taylor Skilling on 10/11/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Stores the word list in a vector, and which includes:
// (a) a function to read the words from the wordlist file
// (b) an overloaded output operator to print the word list
// (c) functions that sort the words using 1) insertionsort, 2) quicksort, and 3) mergesort
// (d) a function to handle word lookups using binary search
// Note: Ensure wordlist.txt path variable is correct

#include "WordList.h"

using namespace std;

// Read words from the wordlist.txt file and store it in the word_list vector
void WordList::ReadWords()
{
    // Initialize variables
    string path_name, line;
    // NOTE: This must be updated when running on a different system
    path_name = "/Users/TaylorSkilling/Documents/Junior NU/Fund. of Algorithims/ski_3a/ski_3a/wordlist.txt";
    ifstream myfile (path_name);
    // Attemp to open the file
    if (myfile.is_open())
    {
        // While the file still has lines to read
        while (getline(myfile,line))
        {
            // Append the line (word) to the vector
            word_list.push_back(line);
        }
        // Close the file
        myfile.close();
    }
    // To Do: Use try/catch
    else cout << "Unable to open file" << endl;
}

// Overloaded output
ostream& operator<<(ostream& os, const WordList& list)
{
    int count(0);
    cout << "The list contains the following words: " << endl;
    for (int i = 0; i < list.word_list.size(); i++) {
        os << list.word_list.at(i) << endl;
        count++;
    }
    cout << "There is a total of: " << count << " words in worldlist.txt" << endl;
    return os;
}

// Insertion Sort
void WordList::InsertionSort(){
    string key;
    // Iterate over all words, starting at index 1
    for (int j = 1; j < word_list.size(); j++) {
        // Set the key as the current word in the outer loop
        key = word_list.at(j);
        // End of the sorted portion
        int i = j-1;
        // While we aren't at the beginning of the list and 
        while (i > 0 && word_list.at(i) > key) {
            // Push item right
            word_list.at(i+1) = word_list.at(i);
            // Update the current index with the key
            word_list.at(i) = key;
            // Decrement the iterator
            i--;
        }
    }
} // end InsertionSort

// Merge
void WordList::Merge(int p, int q, int r)
{
    // Initialize variables
    int i, j, k;
    int n1 = q - p + 1;
    int n2 = r - q;
    
    // create temporary vectors of length n1 and n2
    vector<string> L(n1), R(n2);
    
    // Copy data to temporary vectors L[] and R[] 
    for(i = 0; i < n1; i++)
        L.at(i) = word_list.at(p + i);
    for(j = 0; j < n2; j++)
        R.at(j) = word_list.at(q + j + 1);
    
    // Merge the temporary vectors back into the original vector, this time in order
    i = 0;
    j = 0;
    k = p;              
    
    while (i < n1 && j < n2)
    {
        // If the element in the left vector is less than the one in the right, add it to the new vector, and increment that vector index only
        if (L.at(i) <= R.at(j))
        {
            word_list.at(k) = L.at(i);
            i++;
        }
        // The element in the right vector is less than the one on the left, so add it to the new vector, and increment the appropriate vector
        else
        {
            word_list.at(k) = R.at(j);
            j++;
        }
        k++;
    }
    
    // If there are any remaining elements in L, copy them to the sorted vector
    while (i < n1)
    {
        word_list.at(k) = L.at(i);
        i++;
        k++;
    }
    
    // If there are any remaining elements in R, copy them to the sorted vector
    while (j < n2)
    {
        word_list.at(k) = R.at(j);
        j++;
        k++;
    }
}

// l is for left index and r is right index of the sub-vector of vector to be sorted
void WordList::MergeSort(int l, int r)
{
    if (l < r)
    {
        //int m = l+(r-l)/2; //Same as (l+r)/2, but avoids overflow for large l and h
        int m = floor((l+r)/2);
        MergeSort(l, m);
        MergeSort(m+1, r);
        Merge(l, m, r);
    }
}

// A utility function to swap two elements
void swap(string* a, string* b)
{
    string t = *a;
    *a = *b;
    *b = t;
}

// Quick Sort
// Uses the last element as pivot, places the pivot element at its correct position in sorted array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot
// Input: Left index and right index of vector to sort by
int WordList::Partition (int l, int h)
{
    string x = word_list.at(h);    // pivot
    int i = (l - 1);  // Index of smaller element
    
    for (int j = l; j <= h- 1; j++)
    {
        // If current element is smaller than or equal to pivot
        if (word_list.at(j) <= x)
        {
            i++;    // increment index of smaller element
            swap(&word_list.at(i), &word_list.at(j));  // Swap current element with index
        }
    }
    // Swap the pivot after sorting everything else
    swap(&word_list.at(i+1), &word_list.at(h));
    return (i + 1);
}

// Recursively calls QuickSort to sort a list of strings
// Inputs: Starting index (start) and ending index (end)
void WordList::QuickSort(int start, int end)
{
    if (start < end)
    {
        int p = Partition(start, end); /* Partitioning index */
        QuickSort(start, p - 1);
        QuickSort(p + 1, end);
    }
}

// Binary Search
bool WordList::BinarySearch(string key){
    // Initialize variables
    // Determine the starting and ending index of the vector to sort
    int left(0), right(word_list.size()-1);
    bool debug(false);
    // Main while loop
    while (left <= right)
    {
        int mid((left+right)/2);
        if (word_list.at(mid) == key)
        {
            if (debug == true)
            {
                cout << "Found word: " << word_list.at(mid) << endl;
            }
            return true;
        }
        else if (word_list.at(mid) < key)
        {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return false;
}