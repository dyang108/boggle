/*
* BogSolver.h
* interface for Solver class, which solves the board
* by: Derick Yang
* date: December 1, 2015
*/
#ifndef BOGSOLVER_H
#define BOGSOLVER_H

#include "BogWordList.h"
#include "Dictionary.h"

//
// A class to solve boggle puzzles
//  The class reads in a dictionary and a board
//  Then solves it.
//  Once it has solved it, the solver can be
//  asked for the words it found, can be asked to print the words
//  with their locations, and to print the words just as strings
//

class BogSolver
{
    public:
	BogSolver();
	~BogSolver();
	bool readDict();
	bool readBoard();
	bool solve();                   // search board for words in dict
	int  numWords();                // returns number of words found
	int  numWords(int len);         // number of words of length len
	BogWordList *getWords();        // returns all words found
	BogWordList *getWords(int len); // returns words of len len
	void printWords();              // print all words in HBF
	void printWords(int len);       // print len-length words in HBF
	void listWords();               // print just the text, no coords
	void listWords(int len);        // just the text, no coords
	
   private:
	Dictionary dict;                // must use a Dictionary
	BogWordList *words_found;       // indexes all words based on length
	// only created if getWords() is called
	BogWordList *all_words;
	char **board;                   // char 2D array to store the board
	int width;                      // number of columns in the board
	int height;                     // number of rows in the board
	
	void printBoard();              // print function for debugging
	// helper function the checks for words 
	// from a certain index in the board
	void checkForWordsFrom(int h, int w, BogWord curr, bool* boxes_checked);
	// concatenates a letter to a BogWord
	BogWord addToString(int h, int w, BogWord curr);
	// creates a string out of the BogWord
	string createWord(BogWord curr);
	// inserts a word into the list of word length in sorted manner
	void sortedInsert(int in, BogWord w);
};
#endif
