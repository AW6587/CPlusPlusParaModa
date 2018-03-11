#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
//#include "MODATest.h"
#define NDEBUG   // comment out for cmd line inputs
using namespace std;

int main(int argc, char *argv[])
{
#if DEBUG
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
#endif
    //MODATest.Run(args);
#if DEBUG
    //Console.ReadKey();
#endif
    return 0;
}
