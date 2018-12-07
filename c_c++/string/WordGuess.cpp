/*
 * Guess a secret word (WordGuess.cpp)
 http://www.ntu.edu.sg/home/ehchua/programming/cpp/cp9_String.html
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;
 
const int NUM_WORDS = 18;
const string WORD_LIST[NUM_WORDS] = {
   "apple", "orange", "banana", "watermelon", "pear",
   "pineapple", "papaya", "mango", "grape", "strawberry",
   "lemon", "peach", "cherry", "apricot", "coconut",
   "honeydew", "apricot", "blueberry"};
 
int main() {
   // Seed the pseudo-random number generator
   srand(time(0));
 
   bool over = false;   // gameover
   do {
      string target = WORD_LIST[rand() % NUM_WORDS]; // choose a word between 0 to NUM_WORDS-1
      int target_length = target.length();
      string attempt(target_length, '-');            // init to all dashes
      string badChars;                               // contains bad chars used
      int trial = 1;                                 // number of trials
 
      cout << "Guess the secret word" << endl;
 
      while (attempt != target) {
         char letter;
         cout << "Your guess so far: " << attempt << endl;
         cout << "Trial " << trial << ": Guess a letter: ";
         cin >> letter;
 
         // Check if the letter has been used
         if (badChars.find(letter) != string::npos
               || attempt.find(letter) != string::npos) {
            cout << "You already use this letter. Try again.\n";
            continue;
         }
 
         // Check for good or bad letter
         int pos = target.find(letter);
         if (pos == string::npos) {
            cout << "Oh, bad guess!\n";
            badChars += letter;     // add to badChars string
         } else {
            cout << "Good guess!\n";
            attempt[pos] = letter;
            // Check if this letter appears again later
            do {
               pos = target.find(letter, pos + 1);
               if (pos != string::npos) attempt[pos] = letter;
            } while (pos != string::npos);
         }
 
         ++trial;
      }
 
      cout << "You got it in " << trial << " trials! The secret word is \""
           << target << "\"" << endl;
 
      char playAgain;
      cout << "Another game? <y/n> ";
      cin >> playAgain;
      if (playAgain != 'y' && playAgain != 'Y') over = true;
   } while (!over);
 
   cout << "Bye\n";
   return 0;
}