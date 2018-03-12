#include <iostream>
#include <vector>
#include <sstream>
#include "MODATest.h"
#include "GraphProcessor.h"
#include "ModaAlgorithms.h"

using namespace std;

static string fileName;
static int subGraphSize;
static string action; //runone runmany or runall
static bool useGrochow;
static bool saveOutputs = false;
static string QueryGraphFileName;
static int Threshold;
ModaAlgorithms ModaAlgorithms;

namespace MODATest
{
	bool contains(vector<string> vect, string a)
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

	void parseInput(std::vector<std::string> args)
	{
		action = args[0];

		if(contains(args, "-k"))
		{
			useGrochow = true;
		}

		if(contains(args, "-s"))
		{
			saveOutputs = true;
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

		if(!contains(args, "-t"))
		{
			// error
		}
		else
		{
			for(int i = 0; i < args.size(); i++)
			{
				if(args[i].compare("-t") == 0)
				{
					if(i < args.size() - 1)
					{
						Threshold = stoi(args[i + 1]);
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

		if(!contains(args, "-h"))
		{
			// error
		}
		else
		{
			for(int i = 0; i < args.size(); i++)
			{
				if(args[i].compare("-h") == 0)
				{
					if(i < args.size() - 1)
					{
						QueryGraphFileName = args[i + 1];
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

	void Run(vector<string> args)
	{
		parseInput(args);

		//TODO:
		// ModaAlgorithms.UseModifiedGrochow = useGrochow;

		auto inputGraph = GraphProcessor::LoadGraph(fileName);
		cout << "Input Graph (G): Nodes - " << inputGraph.VertexCount() << "; Edges: " << inputGraph.EdgeCount() << endl;

		if(action.compare("runone") == 0)
		{
			//runone
		}
		else if(action.compare("runmany") == 0)
		{
			//runmany
		}
		else if(action.compare("runall") == 0)
		{
			if (subGraphSize < 3 || subGraphSize > 5)
			{
				cout << "invalid subgraph size" << endl;
			}
			if (subGraphSize >= inputGraph.VertexCount())
			{
				cout << "subgraph size too large for graph" << endl;
			}
			//TODO:
			ModaAlgorithms.BuildTree(subGraphSize);
			Process(action, inputGraph, nullptr, subGraphSize, false);
			return;
		}
		else
		{
			//error
		}

	}

	void Process(string options,
				 UndirectedGraph<int> inputGraph,
				 QueryGraph * queryGraph,
				 int subGraphSize,
				 bool saveTempMappingsToDisk)
	{
		// var threadName = Thread.CurrentThread.ManagedThreadId;
	    if (queryGraph != nullptr)
	    {
			cout << "QueryGraph (H) Nodes - " << queryGraph->VertexCount() << "; Edges: " << queryGraph->EdgeCount() << endl;
	    }
	    clock_t timer;
		int runTime;
	    if (saveTempMappingsToDisk == false)
	    {
	        timer = clock();
	        auto frequentSubgraphs = ModaAlgorithms.Algorithm1(inputGraph, queryGraph, subGraphSize, Threshold);


	        runTime = clock() - timer;

	        int totalMappings = 0;
			ostringstream ss;
			ss << "\nCompleted. Result Summary\n";
	        ss << "-------------------------------------------\n";
	        if (saveOutputs == false)
	        {
				cout << frequentSubgraphs.size() << endl;
	            for (auto & qGraph : frequentSubgraphs)
	            {
					QueryGraph theQGraph = qGraph.first;
	                if (qGraph.second.size() < 1)
	                {
	                    ss << "\tSub-graph: " << theQGraph.ToString() << "\t Mappings: 0\t Is Frequent Subgraph? false\n";
	                }
	                else
	                {
	                    int count = qGraph.second.size(); //int.Parse(qGraph.Value.Split('#')[0]); //
	                    ss << "\tSub-graph: " << theQGraph.ToString() << "\t Mappings: " << count << "\t Is Frequent Subgraph? " << qGraph.first.IsFrequentSubgraph << "\n";
	                    totalMappings += count;
	                }
	            }
				cout << ss.str() << endl;
	        }
	        // else // if (options.SaveOutputs == true)
	        // {
			//
			// 	timer  = clock();
			//
			// 	auto frequentSubgraphs = ModaAlgorithms.Algorithm1_C(inputGraph, queryGraph, subGraphSize, Threshold);
			//
			// 	runTime = clock() - timer;
			//
	        //     for (auto & qGraph : frequentSubgraphs)
	        //     {
			// 		QueryGraph theQGraph = qGraph.first;
	        //         if (qGraph.second.size() < 1)
	        //         {
	        //             ss << "\tSub-graph: " << theQGraph.ToString() << "\t Is Frequent Subgraph? false\n";
	        //         }
	        //         else
	        //         {
	        //             ostringstream fileSS ;
	        //             int count = qGraph.second.size();
	        //             ss << "\tSub-graph: " << theQGraph.ToString() << "\t Mappings: " << count << "\t Is Frequent Subgraph? " << qGraph.first.IsFrequentSubgraph << "\n";
	        //             for (auto & mapping : qGraph.second)
	        //             {
			// 				// fileSS << 's'; // this works
	        //                 fileSS << mapping.GetMappedNodes();
	        //             }
	        //             totalMappings += count;
	        // //             try
	        // //             {
	        // //                 File.WriteAllText(Path.Combine(OUTPUT_DIR, qGraph.Key.Identifier + ".txt"), fileSb.ToString());
	        // //             }
	        // //             catch (Exception ex)
	        // //             {
	        // //                 Console.Error.WriteLine("Failed to write file containing mappings found for querygraph {0} to disk.\n\n{1}", qGraph.Key.Identifier, ex);
	        // //             }
	        //         }
	        //     }
	        // }
	        // sb.AppendFormat("\nTime Taken: {0} ({1}ms)\nNetwork: Nodes - {2}; Edges: {3};\nTotal Mappings found: {4}\nSubgraph Size: {5}\n", sw.Elapsed, sw.ElapsedMilliseconds.ToString("N"), inputGraph.VertexCount, inputGraph.EdgeCount, totalMappings, subGraphSize);
	        // sb.AppendLine("-------------------------------------------\n");
	        // frequentSubgraphs.Clear();
	        // #endregion

	    }

	    // Console.ForegroundColor = ConsoleColor.Blue;
	    // Console.WriteLine(sb);

	    // try
	    // {
	    //     // Dump general result
	    //     File.WriteAllText(Path.GetFileName(options.InputGraphFile) + ".out", sb.ToString());
	    // }
	    // catch { }
	    // sb.Clear();
	}

}
