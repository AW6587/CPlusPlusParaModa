//
//  ModaAlgorithms.cpp
//  483
//  Copyright © 2018 martin. All rights reserved.
//

#include <unordered_set>
#include <vector>
#include "ModaAlgorithms.h"
#include "edge.h"
#include "UndirectedGraph.h"
#include "Mapping.h"
#include "QueryGraph.h"
#include "ExpansionTreeBuilder.h"
using namespace std;

//Constructor
ModaAlgorithms::ModaAlgorithms(){
    //Need to implement
    // MappingNodesComparer = new MappingNodesComparer();/Users/jjja5555/Desktop/CPlusPlusParaModa/Utils.cpp
    _builder = *new ExpansionTreeBuilder<int>(subgraphSize);
}



//Build the tree
void ModaAlgorithms::BuildTree(int subgraphSize){
    _builder.Build();
}

//Return TreeNode
ExpansionTreeNode* ModaAlgorithms::GetNextNode()
{
    if (_builder.VerticesSorted.size() > 0)
    {
        return  _builder.VerticesSorted.front();
        _builder.VerticesSorted.pop();
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
        unordered_set<QueryGraph> treatedNodes;
        //allMapping+
        //allMappings = new map<QueryGraph, string>(_builder.NumberOfQueryGraphs);
        
        do
        {
            //qGraph = GetNextNode()?.QueryGraph;
            if(GetNextNode() != nullptr) qGraph = &GetNextNode()->QueryGraph;
            if (qGraph == nullptr) break;
            
            vector<Mapping> mappings;
            if (qGraph->edgeCount() == (subgraphSize - 1)) // i.e. if qGraph is a tree
            {
                if (UseModifiedGrochow)
                {
                    // Modified Mapping module - MODA and Grockow & Kellis
                    mappings = Algorithm2_Modified(qGraph, inputGraph, numIterations, false);
                }
                else
                {
                    UndirectedGraph<int> inputGraphClone = new UndirectedGraph<int>(inputGraph);
                    mappings = Algorithm2(qGraph, inputGraphClone, numIterations, false);
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
                QueryGraph parentQueryGraph = GetParent(qGraph, _builder.ExpansionTree);
                if (parentQueryGraph.edgeCount() == (subgraphSize - 1))
                {
                    treatedNodes.insert(parentQueryGraph);
                }
                
                string _filename;
                //C# trygetvalue = c++ containskey
                //if (allMappings.TryGetValue(parentQueryGraph, _filename))
                if (allMappings.count(parentQueryGraph))
                {
                    string newFileName; // for parentQueryGraph
                    mappings = Algorithm3(nullptr, inputGraph, qGraph, _builder.ExpansionTree, parentQueryGraph, newFileName, _filename);
                    if (!newFileName.empty()) //C#: !string.IsNullOrWhiteSpace(newFileName)
                    {
                        // We change the _filename value in the dictionary since this means some of the mappings from parent fit the child
                        allMappings[parentQueryGraph] = newFileName;
                    }
                }
                else
                {
                    mappings.clear();//mappings = new Mapping[0];
                }
            }
            
            if (mappings.capacity() > thresholdValue)
            {
                qGraph->IsFrequentSubgraph = true;
            }
            
            // Save mappings.
            string fileName = qGraph->WriteMappingsToFile(mappings);
            if (mappings.capacity() > 0) mappings.clear();
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
            mappings = Algorithm2_Modified(qGraph, inputGraph, numIterations, true);
        }
        else
        {
            mappings = Algorithm2(qGraph, inputGraph, numIterations, true);
        }
        qGraph->RemoveNonApplicableMappings(mappings, inputGraph);
        
        
        //TODO...
        string fileName = "{mappings.Count}#{qGraph.Identifier}.ser";
        //System.IO.File.WriteAllText(fileName, Extensions.CompressString(Newtonsoft.Json.JsonConvert.SerializeObject(mappings)));
        
        if (mappings.capacity() > 0) mappings.clear();
        //allMappings = new map<QueryGraph, string>(1) { { qGraph, fileName } };
        allMappings.clear();
        allMappings[*qGraph] = fileName;
    }
    
    return allMappings;
}

//Algorithm 1
map<QueryGraph, vector<Mapping>> ModaAlgorithms::Algorithm1(UndirectedGraph<int> inputGraph, QueryGraph* qGraph, int subgraphSize = -1, int thresholdValue = 0)
{
    // The enumeration module (Algo 3) needs the mappings generated from the previous run(s)
    map<QueryGraph, vector<Mapping>> allMappings;
    int numIterations = -1;
    if (inputGraph.VertexCount() < 121) numIterations = inputGraph.VertexCount();
    
    if (qGraph == nullptr) // Use MODA's expansion tree
    {
//#region Use MODA's expansion tree
        unordered_set<QueryGraph> treatedNodes;
        //allMappings = new map<QueryGraph, vector<Mapping>>(_builder.NumberOfQueryGraphs);
        
        do
        {
            if(GetNextNode() != nullptr) qGraph = &GetNextNode()->QueryGraph;
            if (qGraph == nullptr) break;
            vector<Mapping> mappings;
            if (qGraph->IsTree(subgraphSize))
            {
                if (UseModifiedGrochow)
                {
                    // Modified Mapping module - MODA and Grockow & Kellis
                    mappings = Algorithm2_Modified(qGraph, inputGraph, numIterations, false);
                }
                else
                {
                    // Mapping module - MODA and Grockow & Kellis.
                    UndirectedGraph<int>* inputGraphClone = new UndirectedGraph<int>(inputGraph);
                    mappings = Algorithm2(qGraph, inputGraphClone, numIterations, false);
                    delete inputGraphClone;
                    inputGraphClone = nullptr;
                }
            }
            else
            {
                // Enumeration moodule - MODA
                // This is part of Algo 3; but performance tweaks makes it more useful to get it here
                QueryGraph parentQueryGraph = GetParent(qGraph, _builder.ExpansionTree);
                if (parentQueryGraph.IsTree(subgraphSize))
                {
                    treatedNodes.insert(parentQueryGraph);
                }
                string file;
                mappings = Algorithm3(allMappings, inputGraph, qGraph, _builder.ExpansionTree, parentQueryGraph, file);
            }
            if (mappings.capacity() > thresholdValue)
            {
                qGraph->IsFrequentSubgraph = true;
            }
            // Save mappings. Do we need to save to disk? Maybe not!
            
            allMappings.insert(pair<QueryGraph,vector<Mapping>>(*qGraph, mappings));
            // Do not call mappings.Clear()
            //mappings = NULL;
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
        if (treatedNodes.size() > 0)
        {
            for (auto const &mapping : allMappings)
            {
                QueryGraph key = mapping.first;
                if (key.IsTree(subgraphSize) && !treatedNodes.count(mapping.first))
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
    else
    {
        vector<Mapping> mappings;
        if (UseModifiedGrochow)
        {
            // Modified Mapping module - MODA and Grockow & Kellis
            mappings = Algorithm2_Modified(qGraph, inputGraph, numIterations, true);
            // mappings = ModaAlgorithm2Parallelized.Algorithm2_Modified(qGraph, inputGraph, numIterations);
        }
        else
        {
            mappings = Algorithm2(qGraph, inputGraph, numIterations, true);
        }
        
        qGraph->RemoveNonApplicableMappings(mappings, inputGraph);
        map<QueryGraph, vector<Mapping>> allMappings;
        allMappings[*qGraph] = mappings;
        
        // Do not call mappings.Clear()
        //
        //mappings = null;
    }
    
    return allMappings;
}



vector<Mapping> ModaAlgorithms::Algorithm2(QueryGraph* queryGraph, UndirectedGraph<int> inputGraphClone, int numberOfSamples, bool getInducedMappingsOnly)
{
    if (numberOfSamples <= 0) numberOfSamples = inputGraphClone.VertexCount() / 3;
    
    
    map<int[], vector<Mapping>> theMappings; //var theMappings = new Dictionary<int[], List<Mapping>>(MappingNodesComparer);
    //Do we really need to implement the mapping nodes comparer?
    vector<int> inputGraphDegSeq = inputGraphClone.GetNodesSortedByDegree(numberOfSamples);
    
    //we dont have vetices and edges in our querygraph?
    int* queryGraphVertices = &queryGraph->Vertices()[0];
    Edge<int>* queryGraphEdges = &queryGraph->Edges()[0];
    
    int subgraphSize = queryGraph->VertexCount();
    //var threadName = System.Threading.Thread.CurrentThread.ManagedThreadId;
    //Console.WriteLine("Thread {0}:\tCallingu Algo 2:\n", threadName);
    for (int i = 0; i < inputGraphDegSeq.capacity(); i++)
    {
        int g = inputGraphDegSeq[i];
        for (int j = 0; j < subgraphSize; j++)
        {
            int h = queryGraphVertices[j];
            if (Utils.CanSupport(queryGraph, h, inputGraphClone, g))
            {
//#region Can Support
                //Remember: f(h) = g, so h is Domain and g is Range
                map<int, int> f;
                f[h] = g;
                vector<int> mappings = Utils.IsomorphicExtension(f, queryGraph, queryGraphEdges, inputGraphClone, getInducedMappingsOnly);
                f.clear();
                if (mappings.capacity() > 0)
                {
                    for (int item : mappings)
                    {
                        if (item.Value.Count > 1)
                        {
                            queryGraph->RemoveNonApplicableMappings(item.Value, inputGraphClone, getInducedMappingsOnly);
                        }
                        //Recall: f(h) = g
                        
                        
                        //NEED TO DO
                        vector<Mapping> maps;
                        if (theMappings.TryGetValue(item.Key, maps))
                        {
                            maps.AddRange(item.Value);
                        }
                        else
                        {
                            theMappings[item.Key] = item.Value;
                        }
                    }
                    mappings.Clear();
                }
                //mappings = null;
//#endregion
            }
        }
        
        //Remove g
        inputGraphClone.RemoveVertex(g);
        if (inputGraphClone.EdgeCount() == 0) break;
    }
    
    //NEED TO DO
    //Array.Clear(queryGraphEdges, 0, queryGraphEdges.Length); C#
    delete queryGraphEdges;
    queryGraphEdges = nullptr;
    //Array.Clear(queryGraphVertices, 0, subgraphSize); C#
    delete queryGraphVertices;
    queryGraphVertices = nullptr;
    inputGraphDegSeq.clear();
    
    vector<Mapping> toReturn = GetSet(theMappings);
    theMappings.clear();
    
    //Console.WriteLine("Thread {0}:\tAlgorithm 2: All tasks completed. Number of mappings found: {1}.", threadName, toReturn.Count);
    return toReturn;
}


vector<Mapping> ModaAlgorithms::Algorithm2_Modified(QueryGraph* queryGraph, UndirectedGraph<int> inputGraph, int numberOfSamples, bool getInducedMappingsOnly)
{
    if (numberOfSamples <= 0) numberOfSamples = inputGraph.VertexCount() / 3;
    
    map<int[], vector<Mapping>> theMappings;
    vector<int> inputGraphDegSeq = inputGraph.GetNodesSortedByDegree(numberOfSamples);
    
    //var threadName = Thread.CurrentThread.ManagedThreadId;
    //Console.WriteLine("Thread {0}:\tCalling Algo 2-Modified:\n", threadName);
    
    Edge<int>* queryGraphEdges = &queryGraph->Edges()[0];
    int h = queryGraph->Vertices()[0];
    map<int, int> f;
    for (int i = 0; i < inputGraphDegSeq.capacity(); i++)
    {
        int g = inputGraphDegSeq[i];
        if (Utils.CanSupport(queryGraph, h, inputGraph, g))
        {
//#region Can Support
            //Remember: f(h) = g, so h is Domain and g is Range
            f[h] = g;
            vector<int> mappings = Utils.IsomorphicExtension(f, queryGraph, queryGraphEdges, inputGraph, getInducedMappingsOnly);
            if (mappings.capacity() > 0)
            {
                for (int item : mappings)
                {
                    // NEED TO DO
                    if (item.Value.Count > 1)
                    {
                        queryGraph->RemoveNonApplicableMappings(item.Value, inputGraph, getInducedMappingsOnly);
                    }
                    //Recall: f(h) = g
                    vector<Mapping> maps;
//                    if (theMappings.TryGetValue(item.Key, out maps))
//                    {
//                        maps.AddRange(item.Value);
//                    }
//                    else
//                    {
//                        theMappings[item.Key] = item.Value;
//                    }
                }
                delete mappings;
            }
            mappings = NULL;
//#endregion
        }
    }
    
    f.clear();
    delete queryGraphEdges;
    queryGraphEdges = nullptr;
    inputGraphDegSeq.clear();
    
    
//    NEEEEEED TO DO
//    var toReturn = GetSet(theMappings);
    theMappings.clear();
    vector<Mapping> toReturn;
    //Console.WriteLine("\nThread {0}:\tAlgorithm 2: All iteration tasks completed. Number of mappings found: {1}.\n", threadName, toReturn.Count);
    return toReturn;
}

//WHat is does line of code do???
//[MethodImpl(MethodImplOptions.AggressiveInlining)]

vector<Mapping> ModaAlgorithms::GetSet(map<int[], vector<Mapping>> theMappings)
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
        
    }

    return toReturn;
}

//Algorithm 3

vector<Mapping> ModaAlgorithms::Algorithm3(map<QueryGraph, vector<Mapping>> allMappings, UndirectedGraph<int> inputGraph, QueryGraph* queryGraph, AdjacencyGraph<ExpansionTreeNode> expansionTree, QueryGraph parentQueryGraph, string newFileName, string fileName = "")
{
    newFileName = "";
    vector<Mapping> parentGraphMappings;
    
    /*
        need to do
        string is null or white space
     
     */
    if (!fileName.empty())
    {
        if (!allMappings.count(parentQueryGraph))
        {
            //Mapping[0]???
            return *new vector<Mapping>;
        }
    }
    else
    {
        parentGraphMappings = parentQueryGraph.ReadMappingsFromFile(fileName);
    }
    
    if (parentGraphMappings.capacity() == 0) return *new vector<Mapping>;
    
    int subgraphSize = queryGraph->VertexCount();
    unordered_set<Edge<int>> parentQueryGraphEdges;
    for (Edge<int> edge : parentQueryGraph.Edges())
    {
        parentQueryGraphEdges.insert(edge);
    }
    Edge<int> newEdge = GetEdgeDifference(*queryGraph, parentQueryGraph, parentQueryGraphEdges);
    parentQueryGraphEdges.clear();
    
    // if it's NOT a valid edge
    //source???
    if (newEdge.Source == Utils.DefaultEdgeNodeVal)
    {
        
        //return new Mapping[0];
        return *new vector<Mapping>;
    }
    
    vector<Mapping> list;
    int oldCount = parentGraphMappings.capacity();
    int id = 0;
    int queryGraphEdgeCount = queryGraph->EdgeCount();
    //Edge<int>[] queryGraphEdges = queryGraph.Edges().ToArray();
    Edge<int>* queryGraphEdges = &queryGraph->Edges()[0];
    
    //NEED TO DO
    vector<Mapping> groupByGNodes = parentGraphMappings.GroupBy(x => x.Function.Values.ToArray(), MappingNodesComparer); //.ToDictionary(x => x.Key, x => x.ToArray(), MappingNodesComparer);
    
    for (Mapping set : groupByGNodes)
    {
        // function.value (= set of G nodes) are all same here. So build the subgraph here and pass it dowm
        var subgraph = Utils.GetSubgraph(inputGraph, set.Key);
        for (item : set)
        {
            item.Id = id++;
            // Remember, f(h) = g
            
            // if (f(u), f(v)) ϵ G and meets the conditions, add to list
            if (item.SubGraphEdgeCount() == queryGraphEdgeCount())
            {
                MappingTestResult isMapping = Utils.IsMappingCorrect2(item.Function, subgraph, queryGraphEdges, true);
                if (isMapping.IsCorrectMapping())
                {
                    list.Add(item);
                }
                isMapping = NULL;
            }
            else if (item.SubGraphEdgeCount() > queryGraphEdgeCount())
            {
                Edge<int> newEdgeImage = item.GetImage(inputGraph, newEdge);
                
                //NEED TO DO
                if (newEdgeImage.Source != Utils.DefaultEdgeNodeVal
                    && inputGraph.ContainsEdge(newEdgeImage.Source, newEdgeImage.Target))
                {
                    list.Add(item);
                }
            }
        }
        subgraph = NULL;
    }
    
    //NEED TO DO
    Array.Clear(queryGraphEdges, 0, queryGraphEdges.Length);
    queryGraphEdges = null;
    var threadName = System.Threading.Thread.CurrentThread.ManagedThreadId;
    
    // Remove mappings from the parent qGraph that are found in this qGraph
    // This is because we're only interested in induced subgraphs
    var theRest = parentGraphMappings.Except(list).ToList();
    parentQueryGraph.RemoveNonApplicableMappings(theRest, inputGraph);
    parentGraphMappings.Clear();
    for (mapping item : theRest)
    {
        parentGraphMappings.push_back(item);
    }
    
    delete theRest;
    theRest = null;
    
    // Now, remove duplicates
    queryGraph.RemoveNonApplicableMappings(list, inputGraph);
    if (!string.IsNullOrWhiteSpace(fileName) && oldCount > parentGraphMappings.Count)
    {
        // This means that some of the mappings from parent fit the current query graph
        newFileName = parentQueryGraph.WriteMappingsToFile(parentGraphMappings);
        try
        {
            System.IO.File.Delete(fileName);
        }
        catch { } // we can afford to let this fail
    }
    
    Console.WriteLine("Thread {0}:\tAlgorithm 3: All tasks completed. Number of mappings found: {1}.\n", threadName, list.Count);
    return list;
}


/// <summary>
/// Helper method for algorithm 3
/// </summary>
/// <param name="queryGraph"></param>
/// <param name="expansionTree"></param>
/// <returns></returns>
[MethodImpl(MethodImplOptions.AggressiveInlining)]
QueryGraph ModaAlgorithms::GetParent(QueryGraph queryGraph, AdjacencyGraph<ExpansionTreeNode> expansionTree)
{
    bool hasNode = expansionTree.ContainsVertex(new ExpansionTreeNode
                                               {
                                                   QueryGraph = queryGraph,
                                               });
    if (hasNode)
    {
        //NEED TO DO
        return expansionTree.Vertices().First(x => !x.IsRootNode && x.NodeName == queryGraph.Identifier).ParentNode.QueryGraph;
    }
    return NULL;
}

/// <summary>
/// Returns the edge in <paramref="currentQueryGraph"/> that is not present in <paramref="parentQueryGraph"/>
/// </summary>
/// <param name="currentQueryGraph">The current subgraph being queried</param>
/// <param name="parentQueryGraph">The parent to <paramref name="currentQueryGraph"/>. This parent is also a subset, meaning it has one edge less.</param>
/// <param name="parentQueryGraphEdges">Edges of <see cref="parentQueryGraph"/>. We send it in to avoid re-computation since we already have it where this method is used</param>
/// <returns></returns>
Edge<int> ModaAlgorithms::GetEdgeDifference(QueryGraph currentQueryGraph, QueryGraph parentQueryGraph, HashSet<Edge<int>> parentQueryGraphEdges)
{
    // Recall: currentQueryGraph is a super-graph of parentQueryGraph
    if ((currentQueryGraph.EdgeCount() - parentQueryGraph.EdgeCount()) != 1)
    {
        //NEED TO DO CONSOLE OUTPUT THING
        Console.WriteLine("Thread {0}:\tInvalid arguments for the method: GetEdgeDifference. [currentQueryGraph.EdgeCount - parentQueryGraph.EdgeCount] = {1}.\ncurrentQueryGraph.Label = '{2}'. parentQueryGraph.Label = '{3}'."
                          , System.Threading.Thread.CurrentThread.ManagedThreadId, (currentQueryGraph.EdgeCount - parentQueryGraph.EdgeCount), currentQueryGraph.Identifier, parentQueryGraph.Identifier);
        return new Edge<int>(Utils.DefaultEdgeNodeVal, Utils.DefaultEdgeNodeVal);
    }
    
    for (Edge<int> edge : currentQueryGraph.Edges())
    {
        if (!parentQueryGraphEdges.Contains(edge))
        {
            return edge;
        }
    }
    return new Edge<int>(Utils.DefaultEdgeNodeVal, Utils.DefaultEdgeNodeVal);
}


