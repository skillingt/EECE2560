//
//  Deck.h
//  ski_2b
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
    Deck(const Deck &);// Copy Constructor
    Deck& operator= (const Deck &); // Overloaded Assignment Operator
    friend ostream& operator<<(ostream& os, const Deck& deck); // Overloaded print operator
    ~Deck (){}; // Destructor
    Card Deal(); // Returns top card in the deck by value and removes it
    void Replace(Card); // Card is passed by value and is added to the end of the deck
    void Shuffle(); // Shuffles cards in random order
};


#endif /* defined(__ski_2a__Deck__) */
