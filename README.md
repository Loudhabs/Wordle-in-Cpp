# Wordle
Text-based version of the word game "Wordle", developed in C++ and using Object Oriented Programming and the BST Data Structure.

# Program/Game description:
	This is a simplified version of the game "Wordle" which is a web-based word game that gained a lot of popularity in 2022.
	Every time the game is lauched, a 5-letter word is randomly selected by the program from the ListOfWords.txt file. 
	This word is set as the secret word, and the user will have to guess it in 6 attempts or less. 
	After every attempt, the user is shown the state of every letter of the word they input, comparing their input to the secret word: 
		1. If the letter is in the secret word and in the correct position, then the status of that letter is 'G' (Green, as in the original Wordle game)
		2. If the letter is in the secret word but in the wrong position, then the status of that letter is 'Y' (Yellow, as in the original Wordle game)
		3. If the letter is not in the secret word, then the status of that letter is '-'

# Program structure and architecture:
	This project uses Object Oriented Programming. It contains a main function and a total of 3 classes: 
		1. The Wordle class
		2. The Tree class
		3. The Node class (Used in the Tree class)
	
	The game "logistics", i.e asking for input, calling for the different functions, and 
	displaying on-screen messages, are included in the main file. 
	The main file calls member functions from the Wordle class. This class contains all the game logic: 
		a. The number of remaining attempts that the user has 
		b. The input check that gets performed after every input, making sure that the user entered a valid 5-letter word from the dictionary
		c. Most important: The member function that compares the input to the secret word, and determines the state of every letter ('G', 'Y', or '-')
		d. Determines when the player has guessed the word

	The program uses a Balanced Binary Search Tree to store the secret word. This data structure comes in handy when 
	trying to determine whether the secret word contains a specific letter, since the BST is known for its search efficiency.
	The Balanced BST has its own class and member functions, and it uses a separate Node class for its nodes.
	The Tree class is able to do the following:
		a. Convert a given string to a BST
		b. Determine whether the Tree contains a certain letter, in efficient time.
