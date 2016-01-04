/*
* BogScorer.h
* implementation for the BogScorer class
* by: Derick Yang
* date: December 1, 2015
*/

#include "BogScorer.h"

// constructor for BogScorer initializes score and the number of
// valid_words
BogScorer::BogScorer() {
	score = 0;
	valid_words = 0; // number of valid words found
}

BogScorer::~BogScorer() {
	// nothing to do
}

// readAnswers reads in all the answers from cin, scoring each one based
// on the length and Boggle's official rules
void BogScorer::readAnswers() {
	string valid;
	while (cin >> valid) {
		Answer a;
		cin >> a.word;
		if (valid == "OK") {	
			a.is_valid = true;
			int length = a.word.length();
			if (length < 5) {
				a.points = 1;
			} else if (length < 6) {
				a.points = 2;
			} else if (length < 7) {
				a.points = 3;
			} else if (length < 8) {
				a.points = 5;
			} else {
				a.points = 11;
			}
		} else {
			a.is_valid = false;
			a.points = 0;
		}
		ans_list.push_back(a);
	}
}

// scoreAnswers adds up the point values of all the valid words
// in the answer list
void BogScorer::scoreAnswers() {
	for (size_t i = 0; i < ans_list.size(); i++) {
		score += ans_list.at(i).points;
		if (ans_list.at(i).is_valid)
			valid_words++; 
	}
}

// printAnswers prints out the results of the scoring in the 
// correct format.
void BogScorer::printAnswers() {
	string validity_str;
	for (size_t i = 0; i < ans_list.size(); i++) {
		if (ans_list.at(i).is_valid)
			validity_str = "OK";
		else
			validity_str = "NO";
		cout << ans_list.at(i).points << " "
		<< validity_str << " " << ans_list.at(i).word << endl;
	}
	cout << valid_words << " words " << score << " points\n";
}



