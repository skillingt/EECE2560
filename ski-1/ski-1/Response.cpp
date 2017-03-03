//
//  Response.cpp
//  ski-1
//
//  Created by Taylor Skilling on 9/17/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
//  Stores the response to a guess (number correct and number incorrect)

#include "Response.h"
#include <iostream>
#include <vector> 

using namespace std;

// Constructor
Response::Response(int number_correct, int number_incorrect)
{
    num_incorrect = number_incorrect;
    num_correct = number_correct;
}

// Prints a response
void Response::PrintResponse()
{
    cout << "The Response is: (" << num_correct << "," << num_incorrect << ")" << endl;
}

// Returns the number of correct digits in the correct place
int Response::GetCorrect()
{
    return num_correct;
}

// Returns the number of correct digits in the incorrect place
int Response::GetIncorrect()
{
    return num_incorrect;
}

// Sets the number of correct digits in the correct place
// Input: Number of digits (int)
void Response::SetCorrect(int n)
{
    num_correct = n;
}

// Sets the number of correct digits in the incorrect place
// Input: Number of digits (int)
void Response::SetIncorrect(int n)
{
    num_incorrect = n;
}

// Compares two Response objects
// Input: A Response object
// Output: Boolean if the Response objects are true or not
bool Response::CompareResponse(Response response_one)
{
    if (response_one.GetCorrect() == GetCorrect() && response_one.GetIncorrect() == GetIncorrect()){
        return true;
    }
    else {
        return false;
    }
}