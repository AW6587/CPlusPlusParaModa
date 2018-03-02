#include <iostream>
#include <vector>
#include "MODATest.h"

using namespace std;

static string fileName; //runone runmany or runall
static int subGraphSize;
static string action;
static bool useGrochow;

bool MODATest::contains(vector<string> vect, string a)
{
	for(int i = 0; i < vect.size(); i++)
	{
		if(vect[i].compare(a) == 0)
		{
			return true;
		}
	}
	return false;
}

void MODATest::parseInput(std::vector<std::string> args)
{
	action = args[0];
	
	if(contains(args, "-k"))
	{
		useGrochow = true;
	}
	
	if(!contains(args, "-g"))
	{
		// error
	}
	else
	{
		for(int i = 0; i < args.size(); i++)
		{
			if(args[i].compare("-g") == 0)
			{
				if(i < args.size() - 1)
				{
					fileName = args[i + 1];
					break;
				}
				else
				{
					//error
					break;
				}
			}
		}
	}


	if(!contains(args, "-n"))
	{
		// error
	}
	else
	{
		for(int i = 0; i < args.size(); i++)
		{
			if(args[i].compare("-n") == 0)
			{
				if(i < args.size() - 1)
				{
					subGraphSize = stoi(args[i + 1]);
					break;
				}
				else
				{
					//error
					break;
				}
			}
		}
	}
}

void MODATest::Run(vector<string> args)
{
	// string fileNameType = args[0]; // runone, runmany, or runall
	// if (fileNameType.compare("runone") != 0 && fileNameType.compare("many") != 0 && fileNameType.compare("runall") != 0)
	// {
	// 	cout << "Error. For more details, run the command: MODA.Console --help" << endl;
	// 	return;
	// }
	parseInput(args);
	cout << fileName << ", " << subGraphSize << ", " << action << ", " << useGrochow << endl;
}
