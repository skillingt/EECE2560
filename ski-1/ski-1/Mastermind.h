//
//  Mastermind.h
//  ski-1
//
//  Created by Taylor Skilling on 9/15/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Mastermind Class prototypes

#ifndef __ski_1__Mastermind__
#define __ski_1__Mastermind__

#include <iostream>
#include "Code.h"
#include "Response.h"

using namespace std;

// Declare the Mastermind class
class Mastermind
{
private:
    Code my_code;
public:
    void PrintCode(Code); // Print a given code
    Code HumanGuess(); // Reads a guess from the keyboard and returns a code object that represents the guess,
    Response GetResponse(Code, Code); // When passed two codes (a guess and the secret code), returns a response
    bool IsSolved(Response); // passed a response and returns true if the response indicates that the board has been solved
    void PlayGame(); // Initializes a random code, prints it to the screen, and then iteratively gets a guess from the user and prints the response until either the codemaker or the codebreaker has won.
};

#endif /* defined(__ski_1__Mastermind__) */
