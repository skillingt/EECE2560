//
//  Deck.cpp
//  ski_2b
//
//  Created by Taylor Skilling on 9/27/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//  Created and Compiled on Mac OS X using Xcode
//
// Declares the member functions of the Deck class, which stores cards in deck order using a linked list of nodes where each node is a single card. Contains a pointer to the first node in the list. Has an overloaded print function which prints all the cards in the list in order from 2 to Ace, Clubs, Diamonds, Hearts, Spades


#include "Deck.h"
#include <vector>

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

// Copy Constructor
Deck::Deck(const Deck &d) {
    front = d.front;
}

// Overloaded Assignment Operator
Deck& Deck::operator= (const Deck &d)
{
    front = d.front;
    // return the existing object
    return *this;
}

// Returns top card in the deck by value and removes it
Card Deck::Deal(){    // Create a pointer
    node<Card> *curr;
    // Create a card object
    Card c;
    // Get a pointer to the top card (front of the list)
    curr = front;
    // Get the Card by value
    c = curr->nodeValue;
    // Change the front of the list to the next node
    front = curr->next;
    // Delete the node
    delete curr;
    return c;
}

// Card is passed by value and is added to the end of the deck
// Input: Card
void Deck::Replace(Card c){
    // Create a pointer
    node<Card> *curr;
    // Start at the top of the deck
    curr = front;
    // Traverse through to the bottom of the deck
    while (curr->next != NULL)
    {
        // Update the pointer to the next in the list
        curr = curr->next;
    }
    // Create a new node pointer
    node<Card> *p;
    // Assign the pointer p a node object of type Card
    p = new node<Card>;
    // Add the card to the end of the deck
    curr->next = p;
    // Assign the values of Card c to the pointer p
    p->nodeValue = c;
}

// Shuffles cards in random order
// Note: Not the ideal algorithim. Could use a variation of merge sort: http://stackoverflow.com/questions/12167630/algorithm-for-shuffling-a-linked-list-in-n-log-n-time
// The below algorithim was more intuitive to me, and the linked list we are working with is relatively small
void Deck::Shuffle(){
    // Declare variables
    int count(0), random_number, seed, vector_size;
    bool debug(false);
    node<Card> *curr;
    vector<string> strings;
    vector<int> values;
    // Start at the front of the list
    curr = front;
    // Traverse the linked list, adding the value and suit of each node to the vector, and determining the total number of nodes
    while (curr != NULL)
    {
        strings.push_back(curr->nodeValue.GetSuit());
        values.push_back(curr->nodeValue.GetValue());
        // Update the pointer to the next in the list
        curr = curr->next;
        count++;
    }
    // Change debug to 1 to view
    if (debug == true) {
        cout << "Value of count is: " << count << endl;
    }
    // Traverse the linked list again, this time, drawing a random number and suit from the vector, before removing them to avoid repetitions
    // Prompt user for seed for random number generation
    cout << "Please input an integer to generate a pseudo-random deck of cards: " << endl;
    cin >> seed;
    // Check to see that seed is an integer
    while(cin.fail()) {
        throw rangeError("Error: Must input an integer to create a seed, exiting the program.");
    }
    // Initialize seed with user input
    srand(seed);
    // Return the pointer to the front of the list
    curr = front;
    // Iterate over the deck of cards
    for (int i = count; i > 0; i--) {
        // Determine the size of the vector, should be the same as i
        vector_size = strings.size();
        if (vector_size != i){
            throw rangeError("Count is not equal to vector_size");
        }
        // Generate a random number between 0 and the length of the vector
        random_number = rand() % vector_size;
        if (debug == true) {
            cout << "The random number for iteration: " << i << " is: " << random_number << endl;
            cout << "Old node: " << curr->nodeValue << endl;
        }
        // Update the node with the new suit and value, taken randomly from the vector
        curr->nodeValue.SetSuit(strings.at(random_number));
        curr->nodeValue.SetValue(values.at(random_number));
        if (debug == true) {
            cout << "New node: " << curr->nodeValue << endl;
        }
        // Remove the taken value and suit from the vectors
        strings.erase(strings.begin() + random_number);
        values.erase(values.begin() + random_number);
        // Update the pointer to the next in the list
        curr = curr->next;
    }
} // end Deck::Shuffle