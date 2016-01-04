/*
* test.cpp
*/
#include <iostream>
#include "BogSolver.h"
using namespace std;

int main() {
	BogSolver solver;
	string word;
	solver.readDict();
	solver.readBoard();
	solver.solve();
	solver.listWords();
	solver.listWords(6);
	solver.printWords();
 	solver.getWords();
	cout << solver.numWords() << endl;
	cout << "# of 5 letter words: " << solver.numWords(5) << endl;
	cout << "# of 6 letter words: " << solver.numWords(6) << endl;
	return 0;
}