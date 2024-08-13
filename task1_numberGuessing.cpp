//1.Number Guessing Game
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
 int main() { // Seed the random number generator with the current time
 srand(time(0)); // Generate a random number between 1 and 100 
 int randomNumber = rand() % 100 + 1;
 int userGuess = 0; 
 
 cout << "Welcome to the Number Guessing Game!" << endl; 
 cout << "I have selected a number between 1 and 100." << endl;
 cout << "Can you guess what it is?" << endl; // Loop until the user guesses the correct number
 
 while (userGuess != randomNumber) {
 cout << "Enter your guess: ";
 cin >> userGuess; 
 if (userGuess < randomNumber) {
     std::cout << "Too low! Try again." << endl;
    } 
    else if (userGuess > randomNumber) {
     cout << "Too high! Try again." << endl;
    } else { 
     cout << "Congratulations! You guessed the correct number." << std::endl; 
    } 
 } 
   return 0;
}

// OUTPUT
/*
Welcome to the Number Guessing Game!
I have selected a number between 1 and 100.
Can you guess what it is?
Enter your guess: 26
Too low! Try again.
Enter your guess: 50
Too high! Try again.
Enter your guess: 30
Too low! Try again.
Enter your guess: 35
Too high! Try again.
Enter your guess: 32
Too high! Try again.
Enter your guess: 33
Too high! Try again.
Enter your guess: 31
Congratulations! You guessed the correct number.
*/ 
