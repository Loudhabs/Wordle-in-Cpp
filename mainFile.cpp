#include <iostream> //for cin/cout
#include <string> //for string class
#include <vector> //for vector arrays
#include <algorithm> //for sort
#include <cstdlib> //for random
#include <ctime> //for random seeding
#include <fstream> //for file opening
#include <cctype> //for toupper()

#include "Wordle.h" //class containing game logic
using namespace std;


//FUNCTION PROTOTYPES//
string convertToUppercase(string str);
string convertToLowercase(string str);
vector<string> importDictionary();
string pickWord(vector<string> arrayOfWords);
string getInput();
void displayResult(int* numArray);
void displayStars();


//MAIN FUNCTION//
int main()
{
	vector<string> dictionaryArray = importDictionary(); //dictionary
	string secretWord = pickWord(dictionaryArray); //selects secret word

	string input;
	int* outputArray;
	int numIterations = 0;

	Wordle theGame(secretWord);
	cout << secretWord << endl;

	while ( theGame.canAttempt() && !(theGame.isSolved()) ) //still can attempt
	{
		displayStars();
		numIterations++;

		cout << "Guess n˚" << numIterations << ": ";
		input = getInput();

		while (!theGame.checkInput(input)) //invalid input
		{
			cout << "Input has to be a 5 letter word.\n";
			cout << "Guess n˚" << numIterations << ": ";
			input = getInput();
		}
		while (!theGame.wordIsInDictionary(dictionaryArray, convertToLowercase(input))) //invalid word
		{
			cout << "This word is not in the dictionary.\n";
			cout << "Guess n˚" << numIterations << ": ";
			input = getInput();
		}

		theGame.updateAttempts(input); //adds input to list of attempts
		outputArray = theGame.compareWord(input); //checks every letter of input

		displayResult(outputArray); //displays result for every input
	}

	//post game results
	if (theGame.isSolved())
		cout << "\nCongrats. You guessed the word!" << endl;
	else if (!theGame.canAttempt())
		cout << "\nYou run out of attempts. The word was '" << secretWord << "'.\n";

	return (0);
} //end main


/*
Utility function. Converts the string input to all uppercase
*/
string convertToUppercase(string str)
{
	//convert string to all uppercase
	for (int i=0; i<str.length(); i++)
	{
		str[i] = toupper(str[i]);
	}
	return str;
} //end convertToUppercase

/*
Utility function. Converts the string input to all lowercase
*/
string convertToLowercase(string str)
{
	//convert string to all uppercase
	for (int i=0; i<str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
	return str;
} //end convertToUppercase


/*
open inputFile, picks 5-letter words, writes them to output file, and adds the words to the vector array.
Returns the vector array
*/
vector<string> importDictionary()
{
	string inFile = "ListOfWords.txt";
	string outFile = "FilteredWords.txt";

	fstream inputFile(inFile, ios::in);
	fstream outputFile(outFile, ios::out);

	const int WORD_LENGTH = 5; //5 letters per word

	string str; //string to store in individual words read from file 
	vector<string> arrayToReturn; //vector array to return

	// int vector.capacity() //returns total capacity of vector
	// int vector.size() //returns size (occupied space) of vector

	while(!inputFile.eof()) //end of file function
	{
		inputFile >> str; //read line/word and assign it to str; will ignore whitespaces

		for (int i=0; i<str.length(); i++)
		{
			if (!isalpha(str[i]))
			{
				str.erase(i, 1);
			}
		}

		if (str.length() == WORD_LENGTH)
		{
	    	outputFile << str << endl; //output to writing file
	    	arrayToReturn.push_back(str); //add to vector array
		}
	} //end while

	sort(arrayToReturn.begin(), arrayToReturn.end()); //using algorithm library

	for (int i=0; i<arrayToReturn.size(); i++)
    	outputFile << arrayToReturn[i] << endl; //output to writing file

	inputFile.close();
	outputFile.close();

	return arrayToReturn; //array containing all 'eligible' words
} //end importDictionary

/*
generates random number, returns a word (the SECRET word, converted to uppercase) selected from the dictionary
*/
string pickWord(vector<string> arrayOfWords)
{
	//seeding random generator
	unsigned seed = time(0);
	srand(seed);

	//generating random number
	int minValue = 1, maxValue = arrayOfWords.size();
	int randomNumber = (rand() % ( maxValue - minValue + 1)) + minValue;

	//retrieving word from file
	string randomWord = arrayOfWords[randomNumber-1];

	//convert word to Uppercase
	randomWord = convertToUppercase(randomWord);

	return randomWord;
} //end pickWord

/*
function to get user input and convert it to uppercase
*/
string getInput()
{
	string guess;
	getline(cin, guess);
	guess = convertToUppercase(guess);
	return guess;
} //end getInput

/*
function that converts the array output by the Wordle class (which has 1's, 2's, and 3's) to a visual output 
of 'G' (for Green letter), 'Y' (for Yellow letter), and '-' (for Gray letter)
*/
void displayResult(int* numArray)
{
	for (int i=0; i<11; i++) //formatting/display purposes
		cout << ' ';

	for (int i=0; i<sizeof(numArray); i++)
	{
		if (numArray[i] == 1)
			cout << 'G';
		else if (numArray[i] == 2)
			cout << 'Y';
		else if (numArray[i] == 3)
			cout << '-';
	}
} //end displayResult

/*
function to display asterixes (formatting/display purposes)
*/
void displayStars()
{
	cout << endl;
	for (int i=0; i<16; i++)
		cout << '*';
	cout << endl;
}

/*
****************
Guess n˚1: Hello
           GG--Y //11 spaces before
****************
*/




//end mainFile.cpp
