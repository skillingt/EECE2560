//
//  Card.h
//  ski_2a
//
//  Created by Taylor Skilling on 9/27/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//

#ifndef __ski_2a__Card__
#define __ski_2a__Card__

#include <iostream>

using namespace std;

// Declare the Card class
class Card
{
private:
    int value;
    string suit;
public:
    Card(){}; // Default Constructor
    Card(int set_value, string set_suit) : value(set_value), suit(set_suit) {}; // Inline Constructor
    friend ostream& operator<<(ostream& os, const Card& card); // Overloaded print operator
    void SetSuit(string suit); // Setter
    void SetValue(int value); // Setter
    string GetSuit(); // Getter
    int GetValue(); // Getter
};

#endif /* defined(__ski_2a__Card__) */
