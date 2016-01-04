# ReadMe for COMP 15 HW6
## Boggle Assignment

1.  The purpose of this program is to run a Boggle game on my website.
	I implemented a solver, a scorer, and a checker for the 
	Boggle game.

2.  BogSolver.h: interface for BogSolver class, which has functionality for
	reading the dictionary and the board, and solving the board. 
    BogSolver.cpp: implementation for the BogSolver class, reads the dictionary
	and the board from cin and uses recursion to solve the board. Also uses
	BogWordList to store words.
    solverMain.cpp: test file for BogSolver class, uses the BogSolver class to 
	read and solve a board.
    BogValidator.h: interface for BogValidator class, which reads a dictionary
	and the board, and determines whether the player answers are valid.
    BogValidator.cpp: uses 3 Dictionaries to check validity of words: a Dictionary
	for the words in the board, a Dictionary of the words the player input, 
	and a Dictionary of words in English. Uses a recursive function to check
	for words in a board.
    checkerMain.cpp: test file for BogValidator class, uses the BogValidator class
	to check the validity of input words, outputting a list of words that are
	OK and not OK.
    BogScorer.h: interface for BogScorer class, which adds up the point values given
	by the output of the BogValidator class. 
    BogScorer.cpp: reads the output of the BogValidator class via cin, and determines
	the correct point value for each word, and outputs the final score and 
	amount of points for each word.
    scorerMain.cpp: test file for BogScorer class, which uses the BogScorer class
	to score a BogValidator output.

3.  Use included Makefile

4.  Outline of data structure (depending on the assignment)
	The Dictionary class uses a Trie to store the words in the English language.
	The Trie is a tree with each node representing a letter, and children of that
	node are next letters in a word. A Trie is particularly useful for looking at
	prefixes of a word, and seeing whether any words start with a certain sequence
	of letters.
	I also used vectors in this assignment, which are dynamic arrays already 
	implemented by the standard template library

5.  Outline of algorithm (depending on the assignment)
In Solver:
	Search for words in board: recursively look at each possible start letter,
	and expand to the letters around that letter that are possible prefixes of
	words.
	Also, in putting the words in the list, each list of words of a certain length
	is sorted alphabetically in the list. This sort-as-you-go is order O(n)
In Validator:
	Build a Dictionary of words in the board by searching the board for words
	in a way similar to that of the Solver.
In Checker:
	Used a simple if statement to have different tiers of score based on the
	length of the word

6.  For vector info: http://www.cplusplus.com/reference/vector/vector/

