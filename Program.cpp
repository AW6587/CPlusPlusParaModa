#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include "MODATest.h"
// #define DEBUG   // comment out for cmd line inputs
using namespace std;
using namespace MODATest;
int main(int argc, char *argv[])
{
#ifdef DEBUG
    string argsStr = "";
    argsStr = "runall -g ..\\SampleInputGraph.txt -n 5 -k"; // -k uses expansion tree
    ////argsStr = @"runall -g ..\Release\Inputs\Ecoli20141001CR_idx.txt -n 5"; // -k uses expansion tree
    ////argsStr = @"runone -g ..\Release\Inputs\SampleInputGraph.txt -h ..\Release\QueryGraphs\4\qg-5a.txt -n 4 -k";

    istringstream iss(argsStr);
    vector<string> args((istream_iterator<string>(iss)), istream_iterator<string>());
    cout << "args = ";
    for(int i = 0; i < args.size(); i++)
    {
            cout << args[i];
    }
#else
    vector<string> args;
    for(int i = 1; i < argc; i++)
    {
        args.push_back(argv[i]);
    }
#endif
    Run(args);
#ifdef DEBUG
    //Console.ReadKey();
#endif
    return 0;
}
