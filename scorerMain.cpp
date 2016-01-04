#include <iostream>

#include "BogScorer.h"

using namespace std;

int main()
{
        BogScorer s;

        s.readAnswers();
        s.scoreAnswers();
        s.printAnswers();

        return 0;
}
