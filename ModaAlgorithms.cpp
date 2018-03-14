//
//  ModaAlgorithms.cpp
//  483
//  Copyright © 2018 martin. All rights reserved.
//

#include <unordered_set>
#include <vector>
#include <sstream>
#include "ModaAlgorithms.h"
#include "edge.h"
#include "UndirectedGraph.h"
#include "Mapping.h"
#include "QueryGraph.h"
#include "ExpansionTreeBuilder.h"
#include "Utils.h"
#include "AdjacencyGraph.h"
using namespace std;
//Constructor
ModaAlgorithms::ModaAlgorithms(){
    //Need to implement

}



//Build the tree
void ModaAlgorithms::BuildTree(int subgraphSize){
    _builder = ExpansionTreeBuilder<int>(subgraphSize);
    _builder.Build();
}

//Return TreeNode
ExpansionTreeNode* ModaAlgorithms::GetNextNode()
{
    if (_builder.VerticesSorted.size() > 0)
    {
        ExpansionTreeNode* temp = new ExpansionTreeNode (_builder.VerticesSorted.front());
        _builder.VerticesSorted.pop();
        return temp;
    }
    return nullptr;
}


//Algorithm 1_C
map<QueryGraph, string> ModaAlgorithms::Algorithm1_C(UndirectedGraph<int> inputGraph, QueryGraph* qGraph, int subgraphSize, int thresholdValue)
{

    // The enumeration module (Algo 3) needs the mappings generated from the previous run(s)
    map<QueryGraph, string> allMappings;
    int numIterations = -1;
    if (inputGraph.VertexCount() < 121) numIterations = inputGraph.VertexCount();

    if (qGraph == nullptr) // Use MODA's expansion tree
    {
        //C# hash set to c++ unordered_set
        unordered_set<QueryGraph, QueryGraphHasher, QueryGraphComparator> treatedNodes;
        //allMapping+
        //allMappings = new map<QueryGraph, string>(_builder.NumberOfQueryGraphs);

        do
        {
            //qGraph = GetNextNode()?.QueryGraph;
            if(GetNextNode() != nullptr) qGraph = new QueryGraph(GetNextNode()->QueryGraph);
            if (qGraph == nullptr) break;

            vector<Mapping> mappings;
            if (qGraph->edgeCount() == (subgraphSize - 1)) // i.e. if qGraph is a tree
            {
                if (UseModifiedGrochow)
                {
                    // Modified Mapping module - MODA and Grockow & Kellis
                    mappings = Algorithm2_Modified(*qGraph, inputGraph, numIterations, false);
                }
                else
                {
                    UndirectedGraph<int> *inputGraphClone = new UndirectedGraph<int>(inputGraph);
                    mappings = Algorithm2(*qGraph, *inputGraphClone, numIterations, false);
                    //delete inputGraphClone;
                    inputGraphClone = nullptr;
                }

                // Because we're saving to file, we're better off doing this now
                qGraph->RemoveNonApplicableMappings(mappings, inputGraph, false);
                treatedNodes.insert(*qGraph);
            }
            else
            {
                // Enumeration moodule - MODA
                // This is part of Algo 3; but performance tweaks makes it more useful to get it here
                QueryGraph *parentQueryGraph = GetParent(qGraph, _builder.ExpansionTree);
                if (parentQueryGraph->edgeCount() == (subgraphSize - 1))
                {
                    treatedNodes.insert(*parentQueryGraph);
                }

                string _filename;

                if (allMappings.count(*parentQueryGraph))
                {
                    string newFileName; // for parentQueryGraph
                    //mappings = Algorithm3(nullptr, inputGraph, qGraph, _builder.ExpansionTree, parentQueryGraph, newFileName, _filename);
                    if (!newFileName.empty()) //C#: !string.IsNullOrWhiteSpace(newFileName)
                    {
                        // We change the _filename value in the dictionary since this means some of the mappings from parent fit the child
                        allMappings[*parentQueryGraph] = newFileName;
                    }
                }
                else
                {
                    mappings.clear();//mappings = new Mapping[0];
                }
            }

            if (mappings.size() > thresholdValue)
            {
                qGraph->IsFrequentSubgraph = true;
            }

            // Save mappings.
            string fileName = qGraph->WriteMappingsToFile(mappings);
            if (mappings.size() > 0) mappings.clear();
            allMappings[*qGraph] = fileName;

            // Check for complete-ness; if complete, break
            if (qGraph->IsComplete(subgraphSize))
            {
                qGraph = nullptr;
                break;
            }
            qGraph = nullptr;
        }
        while (true);
    }
    else
    {
        vector<Mapping> mappings;
        if (UseModifiedGrochow)
        {
            // Modified Mapping module - MODA and Grockow & Kellis
            mappings = Algorithm2_Modified(*qGraph, inputGraph, numIterations, true);
        }
        else
        {
            mappings = Algorithm2(*qGraph, inputGraph, numIterations, true);
        }
        qGraph->RemoveNonApplicableMappings(mappings, inputGraph);


        stringstream fileName;
    	fileName << mappings.size();
    	fileName << "#";
    	fileName << qGraph->Identifier;
    	fileName << ".ser";

    	stringstream ss;
    	ss << "[";

    	int mappingCount = 0;
    	for(auto & mapping : mappings)
    	{
    		mappingCount++;
    		ss << "{\"Id\":" << mapping.Id << ",";
    		ss << "\"Function\":{";
    		int itemCount = 0;
    		for(auto & item : mapping.Function)
    		{
    			itemCount++;
    			ss << "\"" << item.first << "\":" << item.second;
    			if(itemCount < mapping.Function.size())
    			{
    				ss << ",";
    			}
    		}
    		ss << "}";
    		ss << ",\"SubGraphEdgeCount\":" << mapping.SubGraphEdgeCount << "}";
    		if(mappingCount < mappings.size())
    		{
    			ss << ",";
    		}
    	}
    	ss << "]";

    	ofstream outfile;
    	outfile.open(fileName.str());
    	outfile << ss.rdbuf();
    	outfile.close();

        if (mappings.size() > 0) mappings.clear();
        //allMappings = new map<QueryGraph, string>(1) { { qGraph, fileName } };
        allMappings.clear();
        allMappings[*qGraph] = fileName.str();
    }

    return allMappings;
}

//Algorithm 1
map<QueryGraph, vector<Mapping>> ModaAlgorithms::Algorithm1(UndirectedGraph<int> inputGraph, QueryGraph* qGraph, int subgraphSize = -1, int thresholdValue = 0)
{
    /*cout << "START OF ALGO 1\n";
    cout << "-------------------------------------------\n";
    cout << "ExpansionTree vertex cout: " << _builder.ExpansionTree.VertexCount << endl;
    cout << "ExpansionTree edge cout: " << _builder.ExpansionTree.EdgeCount << endl;
    cout << "Inputgraph to String: " << inputGraph.ToString() <<  endl;
    cout <<  endl;*/
    // The enumeration module (Algo 3) needs the mappings generated from the previous run(s)
    
    map<QueryGraph, vector<Mapping>> allMappings;
    
    int numIterations = -1;
    if (inputGraph.VertexCount() < 121) numIterations = inputGraph.VertexCount();
    if (qGraph == nullptr) // Use MODA's expansion tree
    {
//#region Use MODA's expansion tree
        //unordered_set<QueryGraph, QueryGraphHasher, QueryGraphComparator> treatedNodes;
        vector<QueryGraph> treatedNodes;
        //allMappings = new map<QueryGraph, vector<Mapping>>(_builder.NumberOfQueryGraphs);
        int couunter = 0;
        do
        {
            //cout << "Algo1 loop count " << ++couunter << endl;
            //cout << "vertices sorted size: " << _builder.VerticesSorted.size() << endl;
            if(_builder.VerticesSorted.size() > 0)
            {
                //cout << _builder.VerticesSorted.front().QueryGraph.ToString() << endl;
                qGraph = new QueryGraph(_builder.VerticesSorted.front().QueryGraph);
                _builder.VerticesSorted.pop();
            }else
            {
                break;
            }

            vector<Mapping> mappings;
            //cout << "Is tree?" << qGraph->IsTree(subgraphSize) << endl;
            if (qGraph->IsTree(subgraphSize)){
                /*if (UseModifiedGrochow)
                {
                    // Modified Mapping module - MODA and Grockow & Kellis
                    mappings = Algorithm2_Modified(*qGraph, inputGraph, numIterations, false);
                }
                else
                {*/

                    // Mapping module - MODA and Grockow & Kellis.
                    UndirectedGraph<int>* inputGraphClone = new UndirectedGraph<int>(inputGraph);
                    
                    mappings = Algorithm2(*qGraph, inputGraph, numIterations, false);
                    //Delete inputGraphClone
                    delete inputGraphClone;
                    inputGraphClone = nullptr;
                //}
            }
            else{
                // Enumeration moodule - MODA
                // This is part of Algo 3; but performance tweaks makes it more useful to get it here
                QueryGraph* parentQueryGraph = GetParent(qGraph, _builder.ExpansionTree);
                
                //cout << "Parent Is Tree?" << parentQueryGraph->IsTree(subgraphSize) << endl;
                if (parentQueryGraph->IsTree(subgraphSize))
                {
                    treatedNodes.push_back(*parentQueryGraph);
                }
                string file;
                mappings = Algorithm3(allMappings, inputGraph, *qGraph, _builder.ExpansionTree, *parentQueryGraph, file);

            }
            
            if (mappings.size() > thresholdValue)
            {
                qGraph->IsFrequentSubgraph = true;
            }

            //allMappings.insert(pair<QueryGraph,vector<Mapping>>(*qGraph, mappings));
            allMappings[*qGraph] = mappings;
                        // Do not call mappings.Clear()
            // Check for complete-ness; if complete, break
            
            if (qGraph->IsComplete(subgraphSize))
            {
                qGraph = nullptr;
                break;
            }
            qGraph = nullptr;
        }
        while (true);

        //NEED to Work on
        //
        //
        //
        //cout <<"Treated NOdes size: " << treatedNodes.size() << endl;
        if (treatedNodes.size() > 0)
        {
            for (auto &mapping : allMappings)
            {
                QueryGraph key = mapping.first;
                if (key.IsTree(subgraphSize) && !(find(treatedNodes.begin(), treatedNodes.end(), mapping.first) != treatedNodes.end()))
                {
                    key.RemoveNonApplicableMappings(mapping.second, inputGraph);
                }
            }
            treatedNodes.clear();
        }
        //treatedNodes.clear();
        //treatedNodes = nullptr;

        //assign null value to container
    }
    /*else
    {
        vector<Mapping> mappings;
        if (UseModifiedGrochow)
        {
            // Modified Mapping module - MODA and Grockow & Kellis
            mappings = Algorithm2_Modified(*qGraph, inputGraph, numIterations, true);
            // mappings = ModaAlgorithm2Parallelized.Algorithm2_Modified(qGraph, inputGraph, numIterations);
        }
        else
        {
            mappings = Algorithm2(*qGraph, inputGraph, numIterations, true);
        }

        qGraph->RemoveNonApplicableMappings(mappings, inputGraph);
        map<QueryGraph, vector<Mapping>> allMappings;
        allMappings[*qGraph] = mappings;

        // Do not call mappings.Clear()
        //
        //mappings = null;
    }*/
    return allMappings;
}



vector<Mapping> ModaAlgorithms::Algorithm2(QueryGraph queryGraph, UndirectedGraph<int> inputGraphClone, int numberOfSamples, bool getInducedMappingsOnly)
{
    cout << "START OF ALGO 2\n";
    cout << "-------------------------------------------\n";
    if (numberOfSamples <= 0) numberOfSamples = inputGraphClone.VertexCount() / 3;

    Utils helper;
    map<vector<int>, vector<Mapping>> theMappings;
    
    vector<int> inputGraphDegSeq = inputGraphClone.GetNodesSortedByDegree(numberOfSamples);
    vector<int> queryGraphVertices = queryGraph.Vertices();
    vector<Edge<int>> queryGraphEdges = queryGraph.Edges();

    int subgraphSize = queryGraph.VertexCount();

    for (int i = 0; i < inputGraphDegSeq.size(); i++)
    {
        int g = inputGraphDegSeq[i];
        for (int j = 0; j < subgraphSize; j++)
        {
            int h = queryGraphVertices[j];
            if (helper.CanSupport(queryGraph, h, inputGraphClone, g))
            {

                map<int, int> f;
                f[h] = g;
                
                //f size = 1,
                /*cout << "Isomorphic Test: "<< endl;
                cout << "f[" << h << "]" << "= " << g << endl;
                cout << "inputQueryGraph ID: " << queryGraph.Identifier<< endl;
                cout << "queryGraphEdges size: " << queryGraphEdges.size()<< endl;
                cout << "inputGraph toString: " << inputGraphClone.ToString()<< endl;*/
                
                map<vector<int>, vector<Mapping>> mappings = helper.IsomorphicExtension(f, queryGraph, queryGraphEdges, inputGraphClone, getInducedMappingsOnly);
                //cout << endl;
                f.clear();
                if (mappings.size() > 0)
                {
                    for (auto & item : mappings)
                    {
                        if (item.second.size() > 1)
                        {
                            queryGraph.RemoveNonApplicableMappings(item.second, inputGraphClone, getInducedMappingsOnly);
                        }
                        //Recall: f(h) = g

                        //NEED TO DO
                        vector<Mapping> maps;
                        if (theMappings.count(item.first))
                        {
                            //maps.AddRange(item.second);
                            maps.insert( item.second.end(), item.second.begin(), item.second.end() );
                            
                        }
                        else
                        {
                            theMappings[item.first] = item.second;
                        }
                    }
                    mappings.clear();
                }
                //mappings = null;
//#endregion
            }
        }

        //Remove g
        inputGraphClone.RemoveVertex(g);
        if (inputGraphClone.EdgeCount() == 0) break;
    }

    queryGraphEdges.clear();
    inputGraphDegSeq.clear();

    vector<Mapping> toReturn = GetSet(theMappings);
    theMappings.clear();

    //Console.WriteLine("Thread {0}:\tAlgorithm 2: All tasks completed. Number of mappings found: {1}.", threadName, toReturn.Count);
    cout << endl;
    cout << "Algorithm 2 : All tasks completed. Number of mappings found: " << toReturn.size() << endl;
    return toReturn;
}


vector<Mapping> ModaAlgorithms::Algorithm2_Modified(QueryGraph queryGraph, UndirectedGraph<int> inputGraph, int numberOfSamples, bool getInducedMappingsOnly)
{
    if (numberOfSamples <= 0) numberOfSamples = inputGraph.VertexCount() / 3;
    Utils helper;
    map<vector<int>, vector<Mapping>> theMappings;
    vector<int> inputGraphDegSeq = inputGraph.GetNodesSortedByDegree(numberOfSamples);

    cout << "Calling Algo 2-Modified:" << endl;

    vector<Edge<int>> queryGraphEdges = queryGraph.Edges();
    
    int h = queryGraph.Vertices()[0];
    map<int, int> f;
    for (int i = 0; i < inputGraphDegSeq.size(); i++)
    {
        int g = inputGraphDegSeq[i];
        if (helper.CanSupport(queryGraph, h, inputGraph, g))
        {

            f[h] = g;
            map<vector<int>, vector<Mapping>> mappings= helper.IsomorphicExtension(f, queryGraph, queryGraphEdges, inputGraph, getInducedMappingsOnly);
            if (mappings.size() > 0)
            {
                for (auto & item : mappings)
                {
                    
                    if (item.second.size() > 1)
                    {
                        queryGraph.RemoveNonApplicableMappings(item.second, inputGraph, getInducedMappingsOnly);
                    }
                    
                    
                    vector<Mapping> maps;
                    
                    if (theMappings.count(item.first))
                    {
                        maps.insert( maps.end(), item.second.begin(), item.second.end() );
                    }
                    else
                    {
                        theMappings[item.first] = item.second;
                    }
                }
            }
            mappings.clear();
//#endregion
        }
    }

//    NEEEEEED TO DO
    vector<Mapping> toReturn = GetSet(theMappings);
    cout << "Algorithm 2: All iteration tasks completed. Number of mappings found:" << toReturn.size() << endl;
    cout << endl;
    return toReturn;
}

//WHat is does line of code do???
//[MethodImpl(MethodImplOptions.AggressiveInlining)]

vector<Mapping> ModaAlgorithms::GetSet(map<vector<int>, vector<Mapping>> theMappings)
{
    //vector<Mapping> toReturn = new vector<Mapping>(theMappings.Values.SelectMany(s => s));
    //foreach (var set in theMappings.Keys.ToArray())
    //{
    //    foreach (var item in theMappings[set])
    //    {
    //        toReturn.Add(item);
    //    }
    //    theMappings.Remove(set);
    //}
    vector<Mapping> toReturn;
    for (auto const &set : theMappings){
        for (Mapping map : set.second){
            toReturn.push_back(map);
        }
    }

    return toReturn;
}

//Algorithm 3

vector<Mapping> ModaAlgorithms::Algorithm3(map<QueryGraph, vector<Mapping>>allMappings, UndirectedGraph<int> inputGraph, QueryGraph queryGraph, AdjacencyGraph<ExpansionTreeNode> expansionTree, QueryGraph& parentQueryGraph, string& newFileName, string fileName){

    newFileName = "";
    vector<Mapping> parentGraphMappings;
    
    Utils helper;
    
    if (fileName.empty())
    {
        if (allMappings.count(parentQueryGraph)){
            parentGraphMappings = allMappings[parentQueryGraph];
        }else
        {
            
            //Mapping[0]???
            vector<Mapping> output;
            return output;
        }
    }
    else
    {
        cout << "DEBUG" << endl;
        parentGraphMappings = parentQueryGraph.ReadMappingsFromFile(fileName);
        cout << "read file success" << endl;
    }
    
    
    if (parentGraphMappings.size() == 0)
    {
        //Mapping[0]???
        vector<Mapping> output;
        return output;
    }

    int subgraphSize = int(queryGraph.VertexCount());
    vector<Edge<int>> parentQueryGraphEdges;
    //cout << "edges!" << parentQueryGraph->EdgeCount() << endl;
    for (Edge<int> edge : parentQueryGraph.Edges())
    {
        parentQueryGraphEdges.push_back(edge);
    }
    Edge<int> newEdge = GetEdgeDifference(queryGraph, parentQueryGraph, parentQueryGraphEdges);

    if (newEdge.Source == helper.DefaultEdgeNodeVal)
    {
        //Mapping[0]???
        vector<Mapping> output;
        return output;
    }

    vector<Mapping> list;
    int oldCount = int(parentGraphMappings.size());
    int id = 0;
    int queryGraphEdgeCount = queryGraph.EdgeCount();

    
    vector<Edge<int>> queryGraphEdges = queryGraph.Edges();

    map<vector<int>, vector<Mapping>> groupByGNodes;
    for (int i = 0; i < parentGraphMappings.size();i++) {
        vector<int> temp;
        for(auto const& item : parentGraphMappings[i].Function){
            temp.push_back(item.second);
            groupByGNodes[temp].push_back(parentGraphMappings[i]);
        }
    }
    cout << "size:  "  << groupByGNodes.size() << endl;
    //groupByGNodes = parentGraphMappings.GroupBy(x => x.Function.Values.ToArray(), MappingNodesComparer); //.ToDictionary(x => x.Key, x => x.ToArray(), MappingNodesComparer);

    for (auto const& set : groupByGNodes)
    {
        // function.value (= set of G nodes) are all same here. So build the subgraph here and pass it dowm
        UndirectedGraph<int> subgraph = helper.GetSubgraph(inputGraph, set.first);
        for (Mapping item : set.second)
        {
            item.Id = id++;
            // Remember, f(h) = g

            // if (f(u), f(v)) ϵ G and meets the conditions, add to list
            if (item.SubGraphEdgeCount == queryGraphEdgeCount)
            {
                MappingTestResult isMapping = helper.IsMappingCorrect2(item.Function, subgraph, queryGraphEdges, true);
                if (isMapping.IsCorrectMapping)
                {
                    list.push_back(item);
                }
                isMapping.~MappingTestResult();
            }
            else if (item.SubGraphEdgeCount > queryGraphEdgeCount)
            {
                Edge<int> newEdgeImage = item.GetImage(inputGraph, newEdge);

                //NEED TO DO
                if (newEdgeImage.Source != helper.DefaultEdgeNodeVal
                    && inputGraph.ContainsEdge(newEdgeImage.Source, newEdgeImage.Target))
                {
                    list.push_back(item);
                }
            }
        }
        
    }


    // Remove mappings from the parent qGraph that are found in this qGraph
    // This is because we're only interested in induced subgraphs

    vector<Mapping> theRest;
    for(Mapping m : parentGraphMappings){
        if(find(list.begin(), list.end(), m) != list.end()) {
            /* v contains x */
        } else {
            theRest.push_back(m);
        }
    }

    parentQueryGraph.RemoveNonApplicableMappings(theRest, inputGraph);
    parentGraphMappings.clear();
    for (Mapping item : theRest)
    {
        parentGraphMappings.push_back(item);
    }
    
    // Now, remove duplicates
    queryGraph.RemoveNonApplicableMappings(list, inputGraph);
    if (!fileName.empty() && oldCount > parentGraphMappings.size())
    {
        // This means that some of the mappings from parent fit the current query graph
        newFileName = parentQueryGraph.WriteMappingsToFile(parentGraphMappings);
//        try
//        {
//            System.IO.File.Delete(fileName);
//        }
//        catch { } // we can afford to let this fail
    }

//   Console.WriteLine("Thread {0}:\tAlgorithm 3: All tasks completed. Number of mappings found: {1}.\n", threadName, list.Count);
    cout << endl;
    cout << "Algorithm 3: All tasks completed. Number of mappings found:" << list.size() << endl;
    return list;
}


/// <summary>
/// Helper method for algorithm 3
/// </summary>
/// <param name="queryGraph"></param>
/// <param name="expansionTree"></param>
/// <returns></returns>
//[MethodImpl(MethodImplOptions.AggressiveInlining)]
QueryGraph* ModaAlgorithms::GetParent(QueryGraph* queryGraph, AdjacencyGraph<ExpansionTreeNode> & expansionTree)
{
    ExpansionTreeNode qNode;
    qNode.QueryGraph = *queryGraph;
    bool hasNode = expansionTree.ContainsVertex(qNode.QueryGraph);
    if (hasNode)
    {
        //NEED TO DO
//        return expansionTree.Vertices.First(x => !x.IsRootNode && x.NodeName == queryGraph->Identifier).ParentNode.QueryGraph;

        //Find the first node with those condition
        //cout << "Vertices size: " << expansionTree.Vertices.size() << endl;
        for (auto & node : expansionTree.Vertices){
            //cout << node.IsRootNode << node.NodeName << queryGraph->Identifier << endl;
            
            if(!node.IsRootNode && node.NodeName == queryGraph->Identifier){
                //cout << &node.ParentNode->QueryGraph << endl;
                return &(node.ParentNode->QueryGraph);
            }
        }
    }
    return nullptr;
}

/// <summary>
/// Returns the edge in <paramref="currentQueryGraph"/> that is not present in <paramref="parentQueryGraph"/>
/// </summary>
/// <param name="currentQueryGraph">The current subgraph being queried</param>
/// <param name="parentQueryGraph">The parent to <paramref name="currentQueryGraph"/>. This parent is also a subset, meaning it has one edge less.</param>
/// <param name="parentQueryGraphEdges">Edges of <see cref="parentQueryGraph"/>. We send it in to avoid re-computation since we already have it where this method is used</param>
/// <returns></returns>
Edge<int> ModaAlgorithms::GetEdgeDifference(QueryGraph currentQueryGraph, QueryGraph parentQueryGraph, vector<Edge<int>> parentQueryGraphEdges)
{
    Utils helper;
    // Recall: currentQueryGraph is a super-graph of parentQueryGraph
    if ((currentQueryGraph.EdgeCount() - parentQueryGraph.EdgeCount()) != 1)
    {
        cout << "Invalid arguments for the method: GetEdgeDifference. [currentQueryGraph.EdgeCount - parentQueryGraph.EdgeCount] =" << (currentQueryGraph.EdgeCount() - parentQueryGraph.EdgeCount()) << endl;
        cout << "currentQueryGraph.Label = " << currentQueryGraph.Identifier << endl;
        cout << "parentQueryGraph.Label = " << parentQueryGraph.Identifier << endl;
        return Edge<int>(helper.DefaultEdgeNodeVal, helper.DefaultEdgeNodeVal);
    }

    bool containsEdge;
    for (Edge<int> edge : currentQueryGraph.Edges())
    {
        if(find(parentQueryGraphEdges.begin(), parentQueryGraphEdges.end(), edge) != parentQueryGraphEdges.end()) {
            containsEdge = true;
        } else {
            containsEdge = false;
        }
        if (!containsEdge)
        {
            return edge;
        }
    }
    return Edge<int>(helper.DefaultEdgeNodeVal, helper.DefaultEdgeNodeVal);
}
