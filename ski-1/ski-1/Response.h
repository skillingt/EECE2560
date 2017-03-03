//
//  Response.h
//  ski-1
//
//  Created by Taylor Skilling on 9/17/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Response Class prototypes

#ifndef __ski_1__Response__
#define __ski_1__Response__

#include "Code.h"
#include <iostream>

using namespace std;

// Declare the Code class
class Response
{
private:
    int num_correct, num_incorrect;
public:
    Response(){}; // Default Constructor
    Response(int, int); // All Parameters Constructor
    int GetCorrect(); // Getter
    int GetIncorrect(); // Getter
    void SetCorrect(int); // Setter
    void SetIncorrect(int); // Setter
    bool CompareResponse(Response); // Compares a Response to the Response object 
    void PrintResponse(); // Print a Response
    
};

#endif /* defined(__ski_1__Response__) */
