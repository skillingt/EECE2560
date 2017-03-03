//
//  Deck.h
//  ski_2a
//
//  Created by Taylor Skilling on 9/27/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//

#ifndef __ski_2a__Deck__
#define __ski_2a__Deck__

#include <iostream>
#include "d_node.h"
#include "Card.h"

using namespace std;

// Declare the Deck class
class Deck
{
public:
    node<Card> *front; // Pointer to first Card in the deck
    Deck(); // Constructor
    friend ostream& operator<<(ostream& os, const Deck& deck); // Overloaded print operator
};


#endif /* defined(__ski_2a__Deck__) */
