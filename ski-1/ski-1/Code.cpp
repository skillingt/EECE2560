//
//  Code.cpp
//  ski-1
//
//  Created by Taylor Skilling on 9/15/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Method declarations for the Code Class, which stores a code (secret or human guess) and provides helper funtions

#include "Code.h"
#include <vector>
#include <algorithm> // for find function in vector

using namespace std;

// Create randomly generated code
void Code::CreateCode()
{
    int code_length, random_number, seed;
    code_length = 4;
    for (int i = 0; i < code_length; i++)
    {
        // Generate random number between zero and 5
        // Note: Couldn't compile with Xcode using r_random.h
        // Prompt user for seed
        cout << "Please input a seed to generate a pseudo-random number " << i << ":" << endl;
        cin >> seed;
        // Initialize seed with user input
        srand(seed);
        // Generate a random number between 0 and 5
        random_number = rand() % 5;
        code.push_back(random_number);
    }
    return;
}

// Print the code (secret or user given), iterating over each element of the vector
void Code::PrintCode()
{
    cout << "The Code is: ";
    for (int i = 0; i < code.size(); ++i)
    {
        cout << code.at(i);
    }
    cout << endl;
}

// Check for the correct digits in the incorrect location
// Input: An object of the Code class
// Output: The number of correct digits in incorrect locations
int Code::CheckIncorrect(Code check_code)
{
    int incorrect_location = NULL;
    vector<int> bad_digits;
    // Nest for loops to check each digit in the code against all other digits
    for (int k = 0; k < check_code.code.size(); k++)
    {
        for (int i = 0; i < check_code.code.size(); i++)
        {
            // If the digit is in the correct place, add it to the vector of checked digits, break out of the nested loop and check the next digit in the code
            if (check_code.code.at(k) == code.at(k))
            {
                bad_digits.push_back(check_code.code.at(k));
                break;
            }
            // Determine if the two digits are equal, but their indexes are different
            if (check_code.code.at(k) == code.at(i) && k != i)
            {
                // Check to see if the digit has already been exists in the 
                // Determine if vector contains the digit at index k, if it does, then increment
                // Found at: http://stackoverflow.com/questions/3450860/check-if-a-stdvector-contains-a-certain-object
                if(find(bad_digits.begin(), bad_digits.end(), check_code.code.at(k)) != bad_digits.end())
                {
                    // Vector contains the digit already, don't increment, just continue
                    continue;
                } else
                {
                    // Vector of bad digits doesn't include the digit, add it to the vector and increment the counter
                    bad_digits.push_back(check_code.code.at(k));
                    ++ incorrect_location;
                }
            } // end if
        } // end nested for loop
    } // end first for loop
    return incorrect_location;
} // end CheckIncorrect

// Check for the correct digits in the correct location
// Input: An object of the Code class
// Output: The number of correct digits in correct locations
int Code::CheckCorrect(Code check_code)
{
    int correct_location = NULL;
    // If given code isn't the same as the object's code, throw an error
    if (code.size() != check_code.code.size())
    {
        throw rangeError ("User code must be equal in length (4) to secret code");
    }
    // Iterate over codes to determine if the digits are equal
    for (int k = 0; k < check_code.code.size(); k++)
    {
        if (check_code.code.at(k) == code.at(k))
        {
            ++correct_location;
        }
        else
        {
            continue;
        }
    }
    return correct_location;
}

// Setter for the private code in the Code class
// Input: Vector of type int
void Code::SetCode(vector<int> user_input)
{
    code = user_input;
}

// Getter for the private code in the Code class
vector<int> Code::GetCode()
{
    return code;
}