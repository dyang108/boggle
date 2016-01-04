#include <iostream>

#include "BogWordList.h"
#include "Dictionary.h"
#include "BogSolver.h"

using namespace std;

int main()
{
        BogSolver solver;

        solver.readDict();
        solver.readBoard();
        solver.solve();
        solver.printWords();

        return 0;
}
