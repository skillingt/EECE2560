//
//  Code.h
//  ski-1
//
//  Created by Taylor Skilling on 9/15/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Code Class prototypes

#ifndef __ski_1__Code__
#define __ski_1__Code__

#include <iostream>
#include <vector>
#include "d_except.h"
//#include "d_random.h" // Does not work

using namespace std;

// Declare the Code class
class Code
{
private:
    vector<int> code;
public:
    void CreateCode(); // Creates the randomly generated code
    int CheckCorrect(Code); // Returns number of correct digits in correct location
    int CheckIncorrect(Code); // Returns number of correct digits in incorrect location
    void PrintCode(); // Prints the code to the screen
    void SetCode(vector<int>); // Setter
    vector<int> GetCode(); // Getter
};

#endif /* defined(__ski_1__Code__) */
