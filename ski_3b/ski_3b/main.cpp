//
//  main.cpp
//  ski_3b
//
//  Created by Taylor Skilling on 10/18/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Compiled using Xcode on Mac OS X

#include <iostream>
#include <time.h>
#include "WordList.h"
#include "Grid.h"
#include "HashTable.h"
#include "Heap.h"

using namespace std;

// Input: Word list and the Grid
// Prints out all words that can be found in the grid
template <typename T>
vector<string> FindMatches(T &d, Grid &grid){
    // Initialize variables
    string word;
    vector <string> found_words;
    bool isFound(false), debug(false);
    // Iterate through all possible starting positions
    // Iterate through rows
    for (int i = 0; i < grid.GetNumRows(); i++)
    {
        // Iterate through columns
        for (int j = 0; j < grid.GetNumCols(); j++)
        {
            // Iterate through all directions
            for (int m = 0; m < 8; m++)
            {
                // Reinitialize string for a new direction, row, or column
                word = "";
                // Iterate through string length
                for (int k = 0; k < 15; k++)
                {
                    // Build word depending on the row, column, direction and string size
                    word += grid.GetChar(i, j, m, k);
                    // Search the list for the word
                    if (debug == true) {
                        cout << "Searching for the word: " << word << endl;
                    }
                    isFound = d.Search(word);
                    // See if the string is a prefix for any word, break if it's not and check a new direction
                    // If the word is found, print it to the screen
                    if (isFound == true && word.size() > 4)
                    {
                        cout << word << endl;
                        found_words.push_back(word);
                    }
                    // If we reach the 15 character limit, break this loop and try a new direction
                    if (k == 15) {
                        break;
                    }
                }
            }
        }
    }
    return found_words;
}

// Reads the name of the grid file from the keyboard and prints out all words from the word list that can be found in the grid. Prints out the CPU time to sort the words, the CPU time to find the words, and the total time.
// Input: Select the grid used
void Search(int sort, int alg, ostream &file){
    // Initialize variables
    string grid_name, sort_name;
    vector<string> found_words;
    bool isList = true;
    clock_t startTime;
    long diff_sort(0);
    HashTable<string> table;
    // Determine which grid file to load based on user input
    switch (sort) {
        case 1:
            grid_name = "Input15";
            break;
        case 2:
            grid_name = "Input30";
            break;
        case 3:
            grid_name = "Input50";
            break;
        case 4:
            grid_name = "Input250";
            break;
        default:
            break;
    }
    // Read the word list from the wordlist.txt file and populate the initialized object
    WordList list;
    list.ReadWords();
    // Read the grid from the input file and populate the initialized object
    Grid grid;
    grid.ReadGrid(grid_name);
    // Sort the lists using a choice of timed algorithim
    switch (alg) {
        case 5:
        {
            // Insertion Sort
            sort_name = "Insertion";
            startTime = clock();
            list.InsertionSort();
            diff_sort = clock()-startTime;
            cout << list;
            cout << "It took " << (float) diff_sort / CLOCKS_PER_SEC << " seconds to sort the list using Insertion Sort" << endl;
            break;
        }
        case 6:
        {
            // Merge Sort
            sort_name = "Merge";
            startTime = clock();
            list.MergeSort(0, 88994-1);
            diff_sort = clock()-startTime;
            cout << list;
            cout << "It took " << (float) diff_sort / CLOCKS_PER_SEC << " seconds to sort the list using Merge Sort" << endl;
            break;
        }
        case 7:
        {
            // Quick Sort
            sort_name = "Quick";
            startTime = clock();
            list.QuickSort(0, 88994 -1); // Improvement: Don't hard code the total length of the list
            diff_sort = clock()-startTime;
            cout << list;
            cout << "It took " << (float) diff_sort / CLOCKS_PER_SEC << " seconds to sort the list using Quick Sort" << endl;
            break;
        }
        case 8:
        {
            // Heap Sort
            sort_name = "Heap";
            startTime = clock();
            list.HeapSort();
            diff_sort = clock()-startTime;
            cout << list;
            cout << "It took " << (float) diff_sort / CLOCKS_PER_SEC << " seconds to sort the list using Heap Sort" << endl;
            break;
        }
        case 9:
        {
            // Hash Table
            sort_name = "Hash Table";
            // Set the isList variable to false, as this is a hash table
            isList = false;
            // Initialize the clock
            startTime = clock();
            // Get a local copy of the private word list
            vector<string> copy_list;
            copy_list = list.GetList();
            // Copy the word list into the hash table
            for (int i = 0; i < copy_list.size(); i++) {
                table.AddItem(copy_list.at(i));
            }
            diff_sort = clock()-startTime;
            cout << "It took " << (float) diff_sort / CLOCKS_PER_SEC << " seconds to sort the list using a Hash Table" << endl;
            break;
        }
        default:
            break;
    }
    // Find the number of matching words, printing out the time it takes
    startTime = clock(); 
    // Call FindMatches with either a hash table or word list
    if (isList == true)
    {
        found_words = FindMatches(list, grid);
    }
    else
    {
        found_words = FindMatches(table, grid);
    }
    long diff_find = clock()-startTime;
    cout << "It took " << (float) diff_find / CLOCKS_PER_SEC << " seconds to search the list. Used Binary Search: " << isList << endl;
    // Print the total number of words found
    cout << "Found: " << found_words.size() << " words total." << endl;
    // Calculate the total run time of the search and sort
    float total_time = (float) diff_find / CLOCKS_PER_SEC + (float) diff_sort / CLOCKS_PER_SEC;
    // Print the total run time of the sort and search
    cout << "The total run time of the program was: " << total_time << " seconds" << endl;
    // Write to the file the total time and method of search and sort
    file << "Grid: " << grid_name << " Sort: " << sort_name << " Total Time: " << total_time << endl;
}

// Used throughout the developement process to test certain functionality
void TestFunctions()
{
    WordList my_list;
    my_list.ReadWords();
    cout << my_list;
//    my_list.InsertionSort();
//    cout << my_list;
//    my_list.MergeSort(0, 88994-1);
//    cout << my_list;
//    my_list.QuickSort(0, 88994 - 1);
//    cout << my_list;
//    bool isFound;
//    isFound = my_list.BinarySearch("zymotic");
//    cout << isFound;
//    Grid my_grid;
//    my_grid.ReadGrid("Input250");
//    vector<string> found_words;
//    found_words = FindMatches(my_list, my_grid);
//    for (int l = 0; l < found_words.size(); l++) {
//        cout << found_words.at(l) << endl;
//    }
//    cout << "Found: " << found_words.size() << endl;
//    HashTable<string> my_table;
//    string test = "test";
//    my_table.AddItem(test);
//    cout << my_table.InList(test) << endl;
//    my_table.DeleteItem(test);
//    cout << my_table.InList(test) << endl;
//    Heap<string> my_heap;
//    vector<string> my_test{"ZZZ", "ZZ", "DD", "CC", "BB", "BBB", "D", "AAA"};
//    my_heap.InitializeMaxHeap(my_test);
//    for (int i = 0 ; i < my_heap.size(); i++) {
//        cout << my_heap.GetItem(i) << endl;
//    }
//    my_heap.Heapsort(my_heap.size());
//    cout << my_heap;
    my_list.HeapSort();
    cout << my_list;
}

int main(int argc, const char * argv[])
{
    try{
        //TestFunctions();
        cout << "Welcome to Search. We will run through all the possible combinations of search and sort." << endl;
        // Create a file to write to
        ofstream myfile ("/Users/TaylorSkilling/Documents/Junior NU/Fund. of Algorithims/ski_3b/sort_search_output.txt");
        if (myfile.is_open())
        {
            // Two for loops to iterate over all possible grids and searches
            for (int i = 1; i < 5; i++)
            {
                for (int j = 5; j < 10; j++) {
                    // Call the Search algorithim
                    Search(i, j, myfile);
                }
            }
            cout << "Closing the file" << endl;
            // Close the file
            myfile.close();
        }
        else
        {
            // Couldn't open a file to write to
            throw fileError("sort_serach_output.txt");
        }
    } // end try
    catch (const rangeError & re)
    {
        //output the error msg and exit
        cerr << re.what() << endl;
        exit(1);
    }
    catch (const fileError & fe)
    {
        //output the error msg and exit
        cerr << fe.what() << endl;
        exit(1);
    } // end catch
    return 0;
}

