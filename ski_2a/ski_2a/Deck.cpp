//
//  Deck.cpp
//  ski_2a
//
//  Created by Taylor Skilling on 9/27/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Declares the member functions of the Deck class, which stores cards in deck order using a linked list of nodes where each node is a single card. Contains a pointer to the first node in the list. Has an overloaded print function which prints all the cards in the list in order from 2 to Ace, Clubs, Diamonds, Hearts, Spades


#include "Deck.h"

using namespace std;

// Constructor creates deck with ordered cards
Deck::Deck()
{
    // Initialize points to node<Card> objects
    node<Card> *p, *q;
    // Declare array of suits of type string to iterate over
    string suits[] = {"Spades", "Hearts", "Diamonds", "Clubs"};
    // Initialize the front of the linked list with node* p
    p = new node<Card>;
    front = p;
    // Create a Deck of cards
    for (int i = 14; i >= 2; i--)
    {
        for (const string& suit : suits)
        {
            // Create a new node
            q = new node<Card>;
            // Set the value of the node
            q->nodeValue.SetValue(i);
            // Set the suit of the node
            q->nodeValue.SetSuit(suit);
            // Debug: Print the value and suit
            // cout << "New q value: " << q->nodeValue << endl;
            // Check first to see if the list is empty, if so, just make the new node the front
            if (front->nodeValue.GetValue() == 0)
            {
                front = q;
            }
            // If the list isn't empty
            else
            {
                // Add the new node to the front of the list
                q->next = front;
                // Update the front of the list with the newly created node
                front = q;
            }
        };
    }
}

// Overloaded print
ostream& operator<<(ostream& os, const Deck& deck)
{
    cout << "The deck contains the following cards: " << endl;
    // Create a pointer
    node<Card> *curr;
    curr = deck.front; // start at the front
    while (curr != NULL)
    {
        // Use Card class print operator
        os << curr->nodeValue;
        // Update the pointer to the next in the list
        curr = curr->next;
    }
    return os;
}