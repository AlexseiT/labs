#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include "MinimumElementMethod.h"

using namespace std;

int main()
{
    MinimumElementMethod solutionMethod("task3.conf");
    solutionMethod.SolveTransportTask();
    cout << "result Z = " << solutionMethod.GetResult();
}
