#ifndef BOGVALIDATOR_H
#define BOGVALIDATOR_H

#include "Dictionary.h"

class BogValidator
{
public:
	BogValidator();
	~BogValidator();
	bool readDict();                // read in a dictionary
	bool readBoard();               // read in a board
	bool isValid(std::string s);    // validates one word
	void checkWords();              // validates cin.  Goes to EOF.

private:
	// must use a Dictionary for all words
	Dictionary dict;
	// use a Dictionary to store the player answers
	Dictionary player_words;
	// use a Dictionary to store inserted words
	Dictionary board_words;
	 // two dimensional array to hold board of variable size
	char **board;
	int height;                     // height of board
	int width;                      // width of board
	
	bool repeat(string s); // check if word has already been counted
	bool inBoard(string s); // check if word is actually in board
	void populatePossWords(); // populate the possible words in the board
	// search for words given a certain prefix. recursive function
	void addWordsFrom(int h, int w, string curr, bool * boxes_checked); 
};

#endif

