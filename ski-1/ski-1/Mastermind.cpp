//
//  Mastermind.cpp
//  ski-1
//
//  Created by Taylor Skilling on 9/15/15.
//  Copyright (c) 2015 Taylor Skilling. All rights reserved.
//
// Iteratively gets a guess from the user and prints the response until either the codemaker or the codebreaker has won.

#include "Mastermind.h"
#include <vector>
#include <iostream>

using namespace std;

//  Initializes a random code, prints it to the screen, and then iteratively gets a guess from the user and prints the response until either the codemaker or the codebreaker has won
void Mastermind::PlayGame()
{
    // Initialize variables
    Code secret_code, user_code;
    Response response;
    int num_turns = 10, turns_left = 10;
    bool game_over;
    // Greet the User
    cout << "Welcome to Mastermind:" << endl;
    // Initialize the secret code
    secret_code.CreateCode();
    // Print the secret code to the screen
    PrintCode(secret_code);
    for (int i = 0; i < num_turns; i++)
    {
        // Retrieve the user input
        user_code = HumanGuess();
        // Print the user input to the screen
        user_code.PrintCode();
        // Determine the response
        response = GetResponse(user_code, secret_code);
        // Print the response
        response.PrintResponse();
        // Determine if solved
        game_over = IsSolved(response);
        // Determine if game is over or not
        if (game_over == true)
        {
            cout << "Congratulations! You've won." << endl;
            break;
        }
        else
        {
            // Decrement the number of turns left and return to allow the user to input a new guess
            --turns_left;
            cout <<"Sorry, you failed to enter the correct code. You have: " << turns_left << " remaining." << endl;
        }
    } // end for loop
} // end PlayGame()

// Initialize a random code from the Code class and print it to the screen
void Mastermind::PrintCode(Code print_code)
{
    print_code.PrintCode();
    return; 
}

// Reads a guess from the keyboard and returns a code object that represents the guess
Code Mastermind::HumanGuess()
{
    Code user_guess;
    int user_input; 
    vector<int> vector_input;
    cout<<"Please enter a number ranging from 0 to 5 for each requested digit."<<endl;
    for (int k = 0; k < 4; k +=1){
        cout << "Please enter digit: " << k << "." << endl;
        cin >> user_input;
        if (user_input > 5 || user_input < 0){
            throw rangeError ("User input must be equal between 0 and 5");
        }
        vector_input.push_back(user_input);
    }
    // Set the Private variable code with the user input 
    user_guess.SetCode(vector_input);
    return user_guess;
} // end HumanGuess()

// Returns a response when given two codes (a guess and the secret code)
Response Mastermind::GetResponse(Code code_one, Code code_two)
{
    // Instantiate instance of Response class and initialize it using the constructor with the correct and incorrect values 
    Response response;
    int num_correct, num_incorrect;
    num_correct = code_one.CheckCorrect(code_two);
    num_incorrect = code_one.CheckIncorrect(code_two);
    response.SetCorrect(num_correct);
    response.SetIncorrect(num_incorrect);
    return response;
}

// Returns true if the response indicates that the board has been solved
bool Mastermind::IsSolved(Response response)
{
    int num_correct, num_incorrect;
    num_correct = response.GetCorrect();
    num_incorrect = response.GetIncorrect();
    // Condition that would end the game, all digits are correct in the correct position
    if (num_correct == 4 && num_incorrect == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
} // end IsSolved()