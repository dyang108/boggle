/*
* BogValidator.cpp
* implementation for BogValidator class
* by: Derick Yang
* date: December 1, 2015
*/

#include "BogValidator.h"

using namespace std;

// constructor for BogValidator class, 
// initializes the board height and width
BogValidator::BogValidator() {
	height = 0;
	width = 0;
}

// destructor for BogValidator class, deletes the allocated 
// memory for the board.
BogValidator::~BogValidator() {
	for (int i = 0; i < height; i++) {
		delete [] board[i];
	}
	delete [] board;
}

// read in a dictionary.
// returns whether the Dictionary was read in successfully
bool BogValidator::readDict() {
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

// read in a board. Returns whether the board was
// read successfully.
bool BogValidator::readBoard() {
	cin >> height >> width;
	board = new char * [height];
	for (int i = 0; i < height; i++) {
		board[i] = new char [width];
		for (int j = 0; j < width; j++) {
			char c;
			if (!(cin >> c))
				return false;
			c = toupper(c);
			board[i][j] = c;
		}
	}
	return true;
}

// validates one word
// check for repeat answer,
// check for in the board,
// and checks if in the dictionary
bool BogValidator::isValid(string s) {
	if (!dict.isWord(s))
		return false;
	if (repeat(s))
		return false;
	if (!inBoard(s))
		return false;
	else
		return true;
}

// repeat checks for whether or not the
// found word has already been found. Boggle
// does not allow for repeats of the same word
bool BogValidator::repeat(string s) {
	return player_words.isWord(s);
}

// inBoard checks if the words is already in the board
bool BogValidator::inBoard(string s) {
	return board_words.isWord(s);
}

// validates cin.  Goes to EOF.
// checks if each word is valid.
void BogValidator::checkWords() {
	// populate the Dictionary that has all the possible
	// words in the board
	populatePossWords();
	string w;
	
	while (cin >> w) {
		int i = 0;
		while (w[i]) { // convert to upper case
			w[i] = toupper(w[i]);
			i++;
		}
		if (isValid(w)) { // check validity of the word
			cout << "OK " << w << endl;
			player_words.insert(w);
		} else {
			cout << "NO " << w << endl;
		}
	}
}

// populatePossWords populates a Dictionary with all the 
// possible words in a given board.
void BogValidator::populatePossWords() {
	// set a breadcrumb array to keep track of 
	// which boxes have been checked
	bool * boxes_checked = new bool[height * width];
	// initialize all the breadcrumbs to false
	for (int k = 0; k < height * width; k++) {
		boxes_checked[k] = false;
	}
	
	// cycle through each possible starting point, 
	// search for words from there.
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height; j++) {
			addWordsFrom(i, j, "", boxes_checked);
		}
	}
	// free space
	delete [] boxes_checked;
	return;
}

// addWordsFrom is a recursive function that
// searches the board for words when a word is found,
// it will be added to the list 
void BogValidator::addWordsFrom(int h, int w, string curr,
				bool * boxes_checked) {
	if (h < 0 || h >= height || w < 0 || w >= width) {
		return;
	} else if (boxes_checked[h * width + w]) {
		return; // checks if current box has a breadcrumb
	}

	if (board[h][w] == 'Q') // handle the letter Q
		curr += "QU";
	else
		curr += board[h][w];
	// if valid insert the word into board_words
	if (dict.isWord(curr) && curr.length() > 2) {
		board_words.insert(curr);
	}
	// set a breadcrumb before the recursive search
	boxes_checked[h * width + w] = true;
	// search through adjacent boxes
	if (dict.isPrefix(curr)) {
		addWordsFrom(h - 1, w - 1, curr, boxes_checked);
		addWordsFrom(h, w - 1, curr, boxes_checked);
		addWordsFrom(h + 1, w - 1, curr, boxes_checked);
		addWordsFrom(h - 1, w, curr, boxes_checked);
		addWordsFrom(h + 1, w, curr, boxes_checked);
		addWordsFrom(h - 1 , w + 1, curr, boxes_checked);
		addWordsFrom(h, w + 1, curr, boxes_checked);
		addWordsFrom(h + 1, w + 1, curr, boxes_checked);
	}
	// remove breadcrumb from the place
	boxes_checked[h * width + w] = false;
}