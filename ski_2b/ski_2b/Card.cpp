//
//  Card.cpp
//  ski_2b
//
//  Created by Taylor Skilling on 9/27/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// The Card class stores a single card,which includes a value and a suit. Includes constructors, set, and get functions, and an overloaded print operator

#include "Card.h"
#include <iostream> 

// Copy Constructor
Card::Card(const Card &c) { //Copy Constructor
    value = c.value;
    suit = c.suit;
}

// Overloaded Assignment Operator
Card& Card::operator= (const Card &c)
{
    // Copy
    value = c.value;
    suit = c.suit;
    
    // return the existing object
    return *this;
}

// Overloaded print operator
// Inputs: Ostream object and Card object
ostream& operator<<(ostream& os, const Card& card)
{
    switch (card.value) {
        case 11:
            os << "Jack";
            break;
        case 12:
            os << "Queen";
            break;
        case 13:
            os << "King";
            break;
        case 14:
            os << "Ace";
            break;
        default:
            os << card.value;
    }
    os << " of " << card.suit << endl;
    //os << card.value << '/' << card.suit << endl;
    return os;
}

// Setter for the private suit in the Card class
// Input: Suit of type string
void Card::SetSuit(string set_suit)
{
    suit = set_suit;
}

// Setter for the private code in the Code class
// Input: Card value of type int
void Card::SetValue(int set_value)
{
    if (set_value < 2 || set_value > 14)
    {
        throw rangeError("Value must be between 2 and 14");
    }
    value = set_value;
}

// Getter for the private suit in the Card class
string Card::GetSuit()
{
    return suit;
}

// Getter for the private value in the Card class
int Card::GetValue()
{
    return value;
}
