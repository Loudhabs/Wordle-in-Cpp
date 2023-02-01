#include<string> //for string functions
#include <iostream> //for cout, cin
#include <cctype> //for toupper
#include <cstddef> //for nullptr
#include <cmath> //for fabs()
#include <vector> //for vector arrays
#include "Tree.h" //Tree class
#include "Wordle.h" //Wordle class (Game logic)
using namespace std;


//////////////////////////////////////////////////////////////
//      Private Methods Section
//////////////////////////////////////////////////////////////

/*
checks if a letter is in the correct position in the Secret word
*/
bool Wordle::isInPlace(char &ch, int index)
{
	return (ch == theWord[index]);
} //end isInPlace

/*
checks if a letter is in the Secret word
*/
bool Wordle::isInWord(char &ch)
{
	if (isalpha(ch))
		return (treePtr->contains(ch));
	return false;
} //end isInWord

/*
counts the number of occurences of a specific letter in a word
*/
int Wordle::countNumberLetters(char &ch, string word)
{
	int toReturn = 0;

	for (int i=0; i<word.length(); i++)
	{
		if (word[i] == ch)
			toReturn++;
	}
	return toReturn;
} //end countNumberLetters

/*
Recursive Binary Search Algorithm. Used in the function wordIsInDictionary
*/
bool Wordle::binarySearchRecursive(vector<string> array, string input, int left, int right)
{
	if (left>right) //value is not in array
		return false;

	int mid = (left+right)/2;

	if (array[mid] == input) //value found in array
		return true;

	else if (array[mid] > input) //check left side of array
 		return binarySearchRecursive(array, input, left, mid-1);

	else //check right side of array
		return binarySearchRecursive(array, input, mid+1, right);
} //end binarySearchRecursive


//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

Wordle::Wordle() : theWord(" "), NumOfAttempts(0), treePtr(nullptr)
{
} //end default constructor

Wordle::Wordle(const string &secretWord) : theWord(secretWord), NumOfAttempts(0)
{
  	treePtr = new Tree();
	treePtr->setWord(secretWord); //converts a copy of the secret word to a Tree
} //end  constructor

Wordle::~Wordle() //destructor
{
	delete treePtr;
	treePtr = nullptr;
} //end destructor


//////////////////////////////////////////////////////////////
//      PUBLIC METHODS Section
//////////////////////////////////////////////////////////////

/*
returns if user still has unused attempts
*/
bool Wordle::canAttempt()
{
	if ( ((MAX_ATTEMPTS - NumOfAttempts) > 0) && !isSolved() )
		return true;

	return false;
} //end canAttempt

/*
returns if user has guessed the secret word
*/
bool Wordle::isSolved()
{
	bool condition = ( (NumOfAttempts > 0) && (attempts[NumOfAttempts-1] == theWord) );

	return condition;
} //end isSolved

/*
verifies that input has only letters, and that it has 5 of them
*/
bool Wordle::checkInput(const string &input) //returns true if input is a valid 5-letter word
{
	bool condition1 = (input.length() == WORD_SIZE); //verifies that the word is 5 letters
	bool condition2 = true; //verifies that word contains only letters
	// bool condition3 = //check that word is in dictionary

	for (int i=0; i<WORD_SIZE; i++)
	{
		if (!isalpha(input[i]))
		{
			condition2 = false;
			break;
		}
	}
	return (condition1 && condition2);
} //end checkInput

/*
verifies if the user input is in the dictionary
*/
bool Wordle::wordIsInDictionary(vector<string> sortedArrayOfWords, string input)
{	
	int first = 0, last = sortedArrayOfWords.size()-1;

	return binarySearchRecursive(sortedArrayOfWords, 
											input, 
											first, 
											last);
} //end wordIsInDictionary

/*
//adds attempt to the array of attempts.
*/
void Wordle::updateAttempts(const string &lastAttempt)
{
	NumOfAttempts++;
	attempts[NumOfAttempts-1] = lastAttempt;
} //end updateAttempts


/*
returns an array outputArray with the numbers 1, 2, or 3 for each letter. Example output: [3, 3, 2, 1, 3]
1: letter is in correct position
2: letter is not in position, but is in word
3: letter is not in word
*/
int* Wordle::compareWord(const string &input) //returns array with status of every letter in the last attempt
{
	int* outputArray = new int[WORD_SIZE];
	string copy = input; //copy string because every letter used will get "removed" (voided, replaced by a random nonAlpha char)

	int numLetterInSecret; //number of the occurences of a letter in the Secret Word
	int numLetterInInput; //number of the occurences of a letter in the user Input

	//initialize output array with 3's (all letters are initially "not" in secret word)
	for (int i=0; i<WORD_SIZE; i++)
		outputArray[i] = 3;

	//first loop, determine case 1
	for (int i=0; i<WORD_SIZE; i++)
	{
		numLetterInSecret = countNumberLetters(copy[i], theWord); //number of occurences of the current letter in secret word
		numLetterInInput = countNumberLetters(copy[i], input); //number of occurences of the current letter in user input

		if (numLetterInInput > numLetterInSecret)
		{
			if (!isInPlace(copy[i], i))
			{
				outputArray[i] = 3;
				copy[i] = '?'; //'remove' char from word, so that it's not checked again
			}
			else { //there is more than one occurence, but this particular one is in the correct spot
				outputArray[i] = 1;
				copy[i] = '?';
			}
		}

		else if (isInPlace(copy[i], i))
		{
			outputArray[i] = 1;
			copy[i] = '?'; //'remove' char from word, so that it's not checked again
		}

		else if (isInWord(copy[i]))
		{

			outputArray[i] = 2;
			copy[i] = '?'; //'remove' char from word, so that it's not checked again
		}
	}
	return outputArray;
} //end compareWord

//end Wordle.cpp
