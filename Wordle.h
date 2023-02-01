#ifndef WORDLE_H
#define WORDLE_H

#include <string>
#include <vector>
#include "Tree.h"
using namespace std;

//class that contains all game logic
class Wordle
{
private:
	static const int WORD_SIZE = 5; //word size, in letters
	static const int MAX_ATTEMPTS = 6; //number of total attempts allowed

	string theWord; //secret word
	string attempts[MAX_ATTEMPTS];
	int NumOfAttempts;
	Tree* treePtr;

	bool isInPlace(char&, int); //parameters are the character and its index. returns if the letter is in its correct position ("green" status)
	bool isInWord(char&); //parameter is the character. returns if the letter is in the word ("yellow" status)
	
	int countNumberLetters(char&, string); //counts the number of occurences of a specific letter in a word
	bool binarySearchRecursive(vector<string>, string, int, int); //helper of wordIsInDictionary()

public:
	Wordle(); //default constructor
	Wordle(const string&); //constructor, parameter is the secret word
	~Wordle(); //destructor

	bool canAttempt(); //returns if user still has unused attempts
	bool isSolved(); //returns if user guessd the Secret word


	bool checkInput(const string&); //paramter is the input. 
									//verifies that input is 5 letters
	bool wordIsInDictionary(vector<string>, string); //parameters are the dictionary vector and user input.
													//verifies if the user input is in the dictionary
	void updateAttempts(const string&); //parameter is the last attempt. 
									  //adds attempt to the array of attempts.


	int* compareWord(const string&); //parameter is the user input. 
									//returns color of each letter. Important function.
};

#endif

//end Wordle.h