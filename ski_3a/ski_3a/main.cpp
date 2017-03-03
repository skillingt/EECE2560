//
//  main.cpp
//  ski_3a
//
//  Created by Taylor Skilling on 10/11/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Compiled using Xcode on Mac OS X

#include <iostream>
#include <time.h>
#include "WordList.h"
#include "Grid.h"

using namespace std;

// Input: Word list and the Grid
// Prints out all words that can be found in the grid
vector<string> FindMatches(WordList list, Grid grid){
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
                    isFound = list.BinarySearch(word);
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
void Search(int sort, int alg){
    // Initialize variables
    string grid_name;
    vector<string> found_words;
    clock_t startTime;
    long diff_sort(0);
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
            // Insertion Sort
            startTime = clock();
            list.InsertionSort();
            diff_sort = clock()-startTime;
            cout << "It took " << (float) diff_sort / CLOCKS_PER_SEC << " seconds to sort the list using Insertion Sort" << endl;
            cout << list;
            break;
        case 6:
            // Merge Sort
            startTime = clock();
            list.MergeSort(0, 88994-1);
            diff_sort = clock()-startTime;
            cout << "It took " << (float) diff_sort / CLOCKS_PER_SEC << " seconds to sort the list using Merge Sort" << endl;
            cout << list;
            break;
        case 7:
            // Quick Sort
            startTime = clock();
            list.QuickSort(0, 88994 -1); // Improvement: Don't hard code the total length of the list
            diff_sort = clock()-startTime;
            cout << "It took " << (float) diff_sort / CLOCKS_PER_SEC << " seconds to sort the list using Quick Sort" << endl;
            cout << list;
            break;
        default:
            break;
    }
    // Find the number of matching words, printing out the time it takes
    startTime = clock();
    found_words = FindMatches(list, grid);
    long diff_find = clock()-startTime;
    cout << "It took " << (float) diff_find / CLOCKS_PER_SEC << " seconds to search the list" << endl;
    // Print the total number of words found
    cout << "Found: " << found_words.size() << " words total." << endl;
    // Print the total run time of the sort and search
    cout << "The total run time of the program was: " << diff_find/ CLOCKS_PER_SEC +diff_sort/ CLOCKS_PER_SEC << " seconds" << endl;
}

// Used throughout the developement process to test certain functionality
void TestFunctions()
{
    WordList my_list;
    my_list.ReadWords();
    cout << my_list;
    my_list.InsertionSort();
    cout << my_list;
    //my_list.MergeSort(0, 88994-1);
    //cout << my_list;
    //my_list.QuickSort(0, 88994 - 1);
    //cout << my_list;
    //bool isFound;
    //isFound = my_list.BinarySearch("zymotic");
    //cout << isFound;
    Grid my_grid;
    my_grid.ReadGrid("Input250");
    vector<string> found_words;
    found_words = FindMatches(my_list, my_grid);
    for (int l = 0; l < found_words.size(); l++) {
        cout << found_words.at(l) << endl;
    }
    cout << "Found: " << found_words.size() << endl;
}

int main(int argc, const char * argv[])
{
    try{
        //TestFunctions();
        int sort, alg;
        // Prompt user for grid
        cout << "Welcome to Search. Please enter the corresponding number next to the grid size you would like to use: " << endl;
        cout << "1. 15x15" << endl << "2. 30x30" << endl << "3. 50x50" << endl << "4. 250x250" << endl;
        cin >> sort;
        // If the user given number is out of range, throw an error
        if (sort > 4 || sort < 1) {
            throw rangeError("Error: User must input a valid number between 1 and 4");
        }
        cout << "Please enter the corresponding number next to the algorithim you would like to use to sort: " << endl;
        cout << "5. Insertion" << endl << "6. Merge" << endl << "7. Quick" << endl;
        cin >> alg;
        // If the user given number is out of range, throw an error
        if (alg > 7 || alg < 5) {
            throw rangeError("Error: User must input a valid number between 5 and 7");
        }
        // Call the Search algorithim
        Search(sort, alg);
    } catch (const rangeError & re) {
        //output the error msg and exit
        cerr << re.what() << endl;
        exit(1);
    }
    return 0;
}

