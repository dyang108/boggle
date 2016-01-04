/*
* BogSolver.cpp
* implementation for BogSolver class
* by: Derick Yang
* date: December 1, 2015
*/

#include "BogSolver.h"
#include <iostream>
#include <string>

using namespace std;

// constructor for BogSolver, initializing board size and 
// setting all_words to NULL
BogSolver::BogSolver() {
	width = 0;
	height = 0;
	all_words = NULL;
}

// destructor for BogSolver, frees memory allocated throughout
BogSolver::~BogSolver() {
	for (int i = 0; i < height; i++) {
		delete [] board[i];
	}
	delete [] board;
	delete [] words_found;
	delete [] all_words;
}

// read in dictionary into a Dict class
bool BogSolver::readDict() {
	string w;
	while (cin >> w) {
		if (w == ".")
			break;
		int i = 0;
		while (w[i]) {
			 w[i]= toupper(w[i]);
			 i++;
		}
		if (!dict.insert(w))
			break;
	}
	return true;
}

// read in the board to solve.
bool BogSolver::readBoard() {
	cin >> height >> width;
	board = new char * [height];
	
	// read in the board here
	for (int i = 0; i < height; i++) {
		board[i] = new char [width];
		for (int j = 0; j < width; j++) {
			char c;
			if(!(cin >> c))
				return false; // if not readable.
			c = toupper(c);
			board[i][j] = c;
		}
	}
	// initialize a vector to hold all words of all lengths
	// each word of a different size will 
	// be put in a different sublist
	words_found = new BogWordList [width * height];
	return true;
}

// search board for words in dict
bool BogSolver::solve() {
	// initialize a boolean array to keep track of which boxes
	// have been checked.
	bool* boxes_checked = new bool [height * width];
	for (int k = 0; k < height * width; k++) {
		boxes_checked[k] = false;
	}
	
	// cycle through the board, looking at 
	// each tile as a start tile in turn.
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			BogWord w;
			checkForWordsFrom(i, j, w, boxes_checked);
		}
	}
	
	// free memory
	delete [] boxes_checked;
	return true;
}


// helper function for solve(), 
// args: h, the row, w, the column, curr, the current value of the word, 
// boxes_checked, an array of the boxes that have been checked in the board
void BogSolver::checkForWordsFrom(int h, int w, 
				  BogWord curr, bool* boxes_checked) {
	if (h < 0 || h >= height || w < 0 || w >= width) {
		return; // checks if current box is off the board
	} else if (boxes_checked[h * width + w]) {
		return; // checks if current box has already been looked at
	}
	// add the next letter to the string and the BogWord
	curr = addToString(h, w, curr);
	string curr_word = createWord(curr);
	// checks validity of word under Boggle rules
	// add to word list under size
	if (dict.isWord(curr_word) && curr_word.length() > 2) {
		// write this function:
		sortedInsert(curr.size() - 1, curr);
	}

	// mark box as checked before recursion
	boxes_checked[h * width + w] = true;
	if (dict.isPrefix(curr_word)) { // check each adjacent box for words
		checkForWordsFrom(h - 1, w - 1, curr, boxes_checked);
		checkForWordsFrom(h, w - 1, curr, boxes_checked);
		checkForWordsFrom(h + 1, w - 1, curr, boxes_checked);
		checkForWordsFrom(h - 1, w, curr, boxes_checked);
		checkForWordsFrom(h + 1, w, curr, boxes_checked);
		checkForWordsFrom(h - 1 , w + 1, curr, boxes_checked);
		checkForWordsFrom(h, w + 1, curr, boxes_checked);
		checkForWordsFrom(h + 1, w + 1, curr, boxes_checked);
	}
	boxes_checked[h * width + w] = false; // unmark box before returning.
}

// addToString concatenates a character to a BogWord,
BogWord BogSolver::addToString(int h, int w, BogWord curr) {
	BogLett the_letter;
	the_letter.c = board[h][w];
	the_letter.row = h;
	the_letter.col = w;
	
	// this if statement handles the possibility of a Q
	if (board[h][w] == 'Q') {
		BogLett u;
		u.c = 'U';
		u.row = h;
		u.col = w;
		curr.push_back(the_letter);
		curr.push_back(u);
	} else {
		curr.push_back(the_letter);
	}
	return curr;
}

// createWord creates a string from a BogWord
string BogSolver::createWord(BogWord curr) {
	string the_word = "";
	for (size_t i = 0; i < curr.size(); i++) {
		the_word += (curr.at(i)).c;
	}
	return the_word;
}

// sortedInsert inserts a BogWord into the list so that
// the list will be sorted at the end.
void BogSolver::sortedInsert(int in, BogWord w) {
	for (size_t i = 0; i < words_found[in].size(); i++) {
		if (createWord(words_found[in].at(i)).compare(createWord(w))
			> 0) {
			words_found[in].insert(words_found[in].begin() + i, w);
			return;
		}
	}
	words_found[in].push_back(w);
}

// returns number of words found
int  BogSolver::numWords() {
	int total = 0;
	for (int i = 1; i <= width * height; i++) {
		// add number of words at each length
		total += numWords(i);
	}
	return total;
}

// number of words of length len
int  BogSolver::numWords(int len) {
	int count = 0;
	if (words_found[len - 1].size() > 0) {
		count++;
	}
	for (size_t i = 1; i < words_found[len - 1].size(); i++) {
		if (createWord(words_found[len - 1].at(i)) !=
			createWord(words_found[len - 1].at(i - 1))) {
			// if not a duplicate. This is a valid test because
			// the list is sorted alphabetically
			count++;
		}
	}
	return count;
}

// returns all words found
BogWordList *BogSolver::getWords() {
	// initialize all_words to make list from. This list will be 
	// ordered from shortes to longest
	all_words = new BogWordList[numWords()];
	for (int i = width * height; i > 0; i--) {
		BogWordList *curr_sublist = getWords(i);
		for (size_t j = 0; j < curr_sublist->size(); j++) {
			all_words->push_back(curr_sublist->at(j));
		}
	}
	return all_words;
}

// returns words of length len
BogWordList *BogSolver::getWords(int len) {
	return &words_found[len - 1];
}

// print all words in HBF
void BogSolver::printWords() {
	for (int i = width * height; i > 0; i--) {
		printWords(i);
	}
	cout << "< >\n"; // end of list
}

// print the list of len-length words in HBF
void BogSolver::printWords(int len) {
	for (size_t i = 0; i < words_found[len - 1].size(); i++) {
		cout << "< ";
		for (size_t j = 0;
		j < (words_found[len - 1].at(i)).size(); j++) {
			BogLett lett = (words_found[len - 1].at(i)).at(j);
			if (lett.c == 'Q') { // handle Q
				cout << "QU" << " ";
				j++;
			} else {
				cout << lett.c << " "; 
			}
			cout << lett.row << " " << lett.col << " ";
		}
		cout << ">" << endl;
	}
}

// print just the text, no coords
void BogSolver::listWords() {
	for (int i = width * height; i > 0; i--) {
		listWords(i);
	}
}

// just the text, no coords. Lists words of length len
void BogSolver::listWords(int len) {
	if (words_found[len - 1].size() > 0) {
		cout << createWord(words_found[len - 1].at(0)) << endl;
	}
	
	for (size_t i = 1; i < words_found[len - 1].size(); i++) {
		if (createWord(words_found[len - 1].at(i)) !=
			createWord(words_found[len - 1].at(i - 1))) {
			// if not a duplicate. This is a valid test because
			// the list is sorted alphabetically
			cout << createWord(words_found[len - 1].at(i)) 
			<< endl;
		}
	}
}

// printBoard for debugging purposes
void BogSolver::printBoard() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
}








