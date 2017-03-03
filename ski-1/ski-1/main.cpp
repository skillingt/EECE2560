//
//  main.cpp
//  ski-1
//
//  Created by Taylor Skilling on 9/15/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Created using Xcode on Mac OS X
//
// Inititalizes the Mastermind class and begins the game, handling any errors

#include "Mastermind.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]){
    try{
        Mastermind the_master;
        the_master.PlayGame();
    }
    catch (const rangeError & re) {
        //output the error msg and exit
        cerr << re.what() << endl;
        exit(1);
    }
    return 0;
}

