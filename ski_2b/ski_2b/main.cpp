//
//  main.cpp
//  ski_2b
//
//  Created by Taylor Skilling on 10/4/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// The Game of Flip:
// 1. The cards are shuffled three times.
// 2. The player keeps taking cards until the player decides to stop and end the game.
// 3. To take a card, the player turns over the top card on the deck and
//  (a) receives 10 points for an ace,
//  (b) receives 5 points for a king, queen or jack,
//  (c) receives 0 points for an 8, 9 or 10,
//  (d) loses half their points for a 7,
//  (e) loses all their points for a 2, 3, 4, 5 or 6, and
//  (f) receives 1 point extra, in addition to the above, for a heart.
// 4. The goal is to end the game with the most points.

#include <iostream>
#include "d_except.h"
#include "Deck.h"

void PlayFlip(){
    // Initialize variables
    int score(0), user_input;
    // Print a welcome statement to the user
    cout << "Welcome to the Game of Flip!" << endl;
    // Intialize the deck
    Deck my_deck;
    cout << my_deck;
    // Initialize a card
    Card my_card;
    // Shuffle the deck three times
    cout << "The cards will now be shuffled three times" << endl;
    for (int i = 0; i < 3; i++) {
        my_deck.Shuffle();
        cout << my_deck;
    }
    // User interaction and score keeping
    do {
        // Print the users score to the screen
        cout << "Your score is currently: " << score << endl;
        // Accept a user input and determine if they would like to continue playing or not
        cout << "Press a number 1 through 9 to deal a card or '0' to end the game:" << endl;
        cin >> user_input;
        if (user_input == 0)
        {
            cout << "Thank you for playing! Your final score was: " << score << endl;
            break;
        }
        else if (user_input > 0 && user_input < 10)
        {
            cout << "Another card will be drawn from the deck: " << endl;
        }
        else
        {
            throw rangeError("Did not recognize key stroke. The program will now exit");
        }
        // Return a card
        my_card = my_deck.Deal();
        // Print the card to the screen
        cout << "The given card is: " << my_card;
        // Determine points based on the rules:
        //  (a) receives 10 points for an ace,
        //  (b) receives 5 points for a king, queen or jack,
        //  (c) receives 0 points for an 8, 9 or 10,
        //  (d) loses half their points for a 7,
        //  (e) loses all their points for a 2, 3, 4, 5 or 6, and
        //  (f) receives 1 point extra, in addition to the above, for a heart.
        // Check Value
        if (my_card.GetValue() == 14)
        {
            score += 10;
        }
        else if (my_card.GetValue() == 13 || my_card.GetValue() == 12 || my_card.GetValue() == 11)
        {
            score += 5;
        }
        else if (my_card.GetValue() == 10 || my_card.GetValue() == 9 || my_card.GetValue() == 8)
        {
            score += 0;
        }
        else if (my_card.GetValue() == 7)
        {
            score = score/2;
        }
        else if (my_card.GetValue() < 7)
        {
            score = 0;
        }
        // Check for Heart
        if (my_card.GetSuit() == "Hearts")
        {
            score += 1;
        }
        // Return the card to the bottom of the deck
        my_deck.Replace(my_card);
    } while (1); // end do while
} // end PlayFlip()

void TestFunctions(){
    // Intialize the deck
    Deck my_deck;
    // Initialize a card
    Card my_card;
    // Print its contents to the screen, in order
    cout << my_deck;
    // Test the Deal function
    my_card = my_deck.Deal();
    cout << "The top card in the deck is: " << my_card << endl;
    // Test the Replace function
    Card new_card(11,"Hearts");
    my_deck.Replace(new_card);
    cout << my_deck;
    // Test the shuffle function
    my_deck.Shuffle();
    cout << my_deck;
}

int main(int argc, const char * argv[])
{
    try {
        //TestFunctions();
        PlayFlip();
        return 0;
    } catch (const rangeError & re) {
        //output the error msg and exit
        cerr << re.what() << endl;
        exit(1);
    }
}

