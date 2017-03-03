//
//  main.cpp
//  ski_2a
//
//  Created by Taylor Skilling on 9/27/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Initializes a full deck of cards and prints them to the screen in order
// Created on Mac OS X using Xcode

#include <iostream>
#include "d_except.h"
#include "Deck.h"

int main(int argc, const char * argv[])
{
    try {
        // Intialize the deck
        Deck my_deck;
        // Print its contents to the screen, in order
        cout << my_deck;
        return 0;
    } catch (const rangeError & re) {
        //output the error msg and exit
        cerr << re.what() << endl;
        exit(1);
    }
}

