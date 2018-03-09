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
ModaAlgorithms::ModaAlgorithms() : ExpansionTreeBuilder(3){
    //Need to implement
    // MappingNodesComparer = new MappingNodesComparer();
}

//Build the tree
void ModaAlgorithms::BuildTree(int subgraphSize){
    //Need to implement
    _builder = new ExpansionTreeBuilder<int>(subgraphSize);
    _builder.Build();
}

//Return TreeNode
ExpansionTreeNode ModaAlgorithms::GetNextNode()
{
    if (_builder.VerticesSorted.Count > 0)
    {
        return _builder.VerticesSorted.Dequeue();
    }
    return NULL;
}


//Algorithm 1
map<QueryGraph, string> ModaAlgorithms::Algorithm1_C(UndirectedGraph<int> inputGraph, QueryGraph qGraph, int subgraphSize, int thresholdValue)
{
    
    // The enumeration module (Algo 3) needs the mappings generated from the previous run(s)
    map<QueryGraph, string> allMappings;
    int numIterations = -1;
    if (inputGraph.VertexCount() < 121) numIterations = inputGraph.VertexCount();
    
    if (qGraph == nullptr) // Use MODA's expansion tree
    {
        //C# hash set to c++ unordered_set
        unordered_set<QueryGraph> treatedNodes = new unordered_set<QueryGraph>();
        allMappings = new map<QueryGraph, string>(_builder.NumberOfQueryGraphs);
        do
        {
            //qGraph = GetNextNode()?.QueryGraph;
            if(GetNextNode() != nullptr) qGraph = GetNextNode().QueryGraph;
            if (qGraph == null) break;
            
            vector<Mapping> mappings;
            if (qGraph.EdgeCount == (subgraphSize - 1)) // i.e. if qGraph is a tree
            {
                if (UseModifiedGrochow())
                {
                    // Modified Mapping module - MODA and Grockow & Kellis
                    mappings = Algorithm2_Modified(qGraph, inputGraph, numIterations, false);
                }
                else
                {
                    UndirectedGraph<int> inputGraphClone = inputGraph.Clone();
                    mappings = Algorithm2(qGraph, inputGraphClone, numIterations, false);
                    inputGraphClone.Clear();
                    inputGraphClone = nullptr;
                }
                
                // Because we're saving to file, we're better off doing this now
                qGraph.RemoveNonApplicableMappings(mappings, inputGraph, false);
                treatedNodes.Add(qGraph);
            }
            else
            {
                // Enumeration moodule - MODA
                // This is part of Algo 3; but performance tweaks makes it more useful to get it here
                QueryGraph parentQueryGraph = GetParent(qGraph, _builder.ExpansionTree);
                if (parentQueryGraph.EdgeCount() == (subgraphSize - 1))
                {
                    treatedNodes.Add(parentQueryGraph);
                }
                string _filename;
                if (allMappings.TryGetValue(parentQueryGraph, out_filename))
                {
                    string newFileName; // for parentQueryGraph
                    mappings = Algorithm3(null, inputGraph, qGraph, _builder.ExpansionTree, parentQueryGraph, out newFileName, _filename);
                    if (!string.IsNullOrWhiteSpace(newFileName))
                    {
                        // We change the _filename value in the dictionary since this means some of the mappings from parent fit the child
                        allMappings[parentQueryGraph] = newFileName;
                    }
                }
                else
                {
                    mappings = new Mapping[0];
                }
            }
            
            if (mappings.capacity() > thresholdValue)
            {
                qGraph.IsFrequentSubgraph = true;
            }
            
            // Save mappings.
            var fileName = qGraph.WriteMappingsToFile(mappings);
            if (mappings.capacity() > 0) mappings.clear();
            allMappings[qGraph] = fileName;
            
            // Check for complete-ness; if complete, break
            if (qGraph.IsComplete(subgraphSize))
            {
                qGraph = null;
                break;
            }
            qGraph = null;
        }
        while (true);
#endregion
    }
    else
    {
        vector<Mapping> mappings;
        if (UseModifiedGrochow())
        {
            // Modified Mapping module - MODA and Grockow & Kellis
            mappings = Algorithm2_Modified(qGraph, inputGraph, numIterations, true);
        }
        else
        {
            mappings = Algorithm2(qGraph, inputGraph, numIterations, true);
        }
        qGraph.RemoveNonApplicableMappings(mappings, inputGraph);
        
        //var fileName = $"{mappings.Count}#{qGraph.Identifier}.ser";
        //System.IO.File.WriteAllText(fileName, Extensions.CompressString(Newtonsoft.Json.JsonConvert.SerializeObject(mappings)));
        
        if (mappings.capacity() > 0) mappings.clear();
        allMappings = new map<QueryGraph, string>(1) { { qGraph, fileName } };
    }
    
    return allMappings;
}

//Algorithm 2
vector<Mapping> ModaAlgorithms::Algorithm2(QueryGraph queryGraph, UndirectedGraph<int> inputGraphClone, int numberOfSamples, bool getInducedMappingsOnly)
{
    if (numberOfSamples <= 0) numberOfSamples = inputGraphClone.VertexCount() / 3;
    
    // Do we need this clone? Can't we just remove the node directly from the graph?
    // We do need it.
    
    map<int[], List<Mapping>>(MappingNodesComparer) theMappings;
    
    
    //Need to implement next
    var inputGraphDegSeq = inputGraphClone.GetNodesSortedByDegree(numberOfSamples);
    var queryGraphVertices = queryGraph.Vertices.ToArray();
    var queryGraphEdges = queryGraph.Edges.ToArray();
    var subgraphSize = queryGraphVertices.Length;
    var threadName = System.Threading.Thread.CurrentThread.ManagedThreadId;
    Console.WriteLine("Thread {0}:\tCallingu Algo 2:\n", threadName);
    for (int i = 0; i < inputGraphDegSeq.Count; i++)
    {
        var g = inputGraphDegSeq[i];
        for (int j = 0; j < subgraphSize; j++)
        {
            var h = queryGraphVertices[j];
            if (Utils.CanSupport(queryGraph, h, inputGraphClone, g))
            {
#region Can Support
                //Remember: f(h) = g, so h is Domain and g is Range
                var f = new Dictionary<int, int>(1);
                f[h] = g;
                var mappings = Utils.IsomorphicExtension(f, queryGraph, queryGraphEdges, inputGraphClone, getInducedMappingsOnly);
                f.Clear();
                f = null;
                if (mappings.Count > 0)
                {
                    foreach (var item in mappings)
                    {
                        if (item.Value.Count > 1)
                        {
                            queryGraph.RemoveNonApplicableMappings(item.Value, inputGraphClone, getInducedMappingsOnly);
                        }
                        //Recall: f(h) = g
                        List<Mapping> maps;
                        if (theMappings.TryGetValue(item.Key, out maps))
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
                mappings = null;
#endregion
            }
        }
        
        //Remove g
        inputGraphClone.RemoveVertex(g);
        if (inputGraphClone.EdgeCount == 0) break;
    }
    Array.Clear(queryGraphEdges, 0, queryGraphEdges.Length);
    queryGraphEdges = null;
    Array.Clear(queryGraphVertices, 0, subgraphSize);
    queryGraphVertices = null;
    inputGraphDegSeq.Clear();
    inputGraphDegSeq = null;
    
    var toReturn = GetSet(theMappings);
    theMappings = null;
    
    Console.WriteLine("Thread {0}:\tAlgorithm 2: All tasks completed. Number of mappings found: {1}.", threadName, toReturn.Count);
    return toReturn;
}
