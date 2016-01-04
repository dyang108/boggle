/*
* BogScorer.h
* 
*/

/*
* BogScorer.h
* interface for scorer class, which scores the answers
* by: Derick Yang
* date: December 1, 2015
*/

#ifndef BOGSCORER_H
#define BOGSCORER_H

#include <vector>
#include <iostream>

using namespace std;

class BogScorer {
	public:
		BogScorer();
		~BogScorer();
		void readAnswers();
		void scoreAnswers();
		void printAnswers();
		
	private:
		struct Answer { // struct to store each answer
			string word;
			bool is_valid;
			int points;
		};
		vector<Answer> ans_list; // vector to store answers
		int score; // cumulative score
		int valid_words; // cumulative number of words
};

#endif