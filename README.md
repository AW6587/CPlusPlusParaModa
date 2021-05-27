ParaMODA in C++ 

## Introduction
Protein to protein interactions (PPI) are contacts between two or more protein molecules, due to biochemical events, forming large networks. These networks can be represented as graphs. A recurrent, statistically significant subgraph of the larger network, is called a network motif. Motifs are of interest to many researchers as they may reveal functional properties of their structures. Discovering such motifs is computationally intensive and many computer algorithms have been proposed to solve this challenging problem. 

ParaMODA is a motif-centric network motif detection tool. It expands upon earlier algorithms, Groshow-Kellis and MODA, by providing alterations to the original implementations as well as adding additional functionality. While traditional approaches to motif finding are to traverse an entire network to enumerate all possible subgraphs, researchers who are interested in finding a particular set of subgraphs in a network are able to save time using ParaMODA by eliminating redundant work by ignoring subgraphs that are not of interest. 
  
ParaMODA is implemented in the C# language which is Microsoft specific and not ideal in all environments. We have sought to reimplement the original program in C++ to be more compatible with the Bioinformatics digital library at the University of Washington, Bothell. In this paper, we outline our methods used, give an overview of our work so far, describe the data input, outline our testing process, and discuss the results.

## Methods
As previously mentioned, we chose to reimplement ParaMODA in the C++ programming language. Our reasoning for doing so was based on a few factors. We felt it would be most appropriate in the University’s Linux environment, as it can be run natively through the command line without the need for added complications. This also served our team well since two of the three were using Macbook Pros, operating on a Unix OS, which streamlined the process to a degree. It is likely that the code may not run as expected on a Windows based computer due to some differences in syntax. We also chose C++ as the language that most of us (and most UWB students) are familiar with. To manage the difficult task of version control, we used Github as our code repository.
  
## Program Description
ParaMODA motif-centric approach searches for specific subgraph patterns in a particular network of interest. The algorithm finds instances of a certain graph pattern in a predefined query set. The query graphs are ordered into an expanding tree, added via a breadth first traversal, and only subgraphs of a certain size are examined. It adds speed by being able to find a single motif query or a small number of motif queries with larger sizes instead of searching all possible subgraphs of a given size.
  
Outputs are then reused in subsequent searches to speed up the searching time. Additional work is simplified by sampling only a subset of nodes in a give network, removing the need to find all mappings. ParaMODA’s subgraph selection utilizes isomorphic testing by determining if a graph has a specific set of invariants, which are properties inherent to a graph structure.
  
The algorithm is described as such:<br/>
  **Input:** Graph _G_ and a query graph _H_ <br/>
  **Output:** A set of all instances of _H_ in _G_ <br/>
  Start with an empty set of instances <br/>
  Order the nodes of _G_ by increasing degree and then by increasing neighbor degree sequence <br/>
  **Pick any node _h_ from _H_** <br/>
  **for** each node _g_ of _G_ **do** <br/>
    **for** each node _h_ of _H_ such that _g_ can support _h_ **do** <br/>
      Let _f_ be the partial map associating _f(h) = g_ <br/>
      Find all isomorphic extensions of _f_ <br/>
      (i.e. call IsomorphicExtensions(_f,H,G_)) <br/>
      Add the images of these maps to the set of all instances <br/>
  **Return** the set of all instances (Mbadiwe, Kim)
  
ParaMODA is a robust program and we were unable to implement it in its entirety due to timing constraints. By running the original implementation in C#, with the first provided test, we mapped the the file dependencies used. 

As detailed in ParaMODA’s documentation, the original C# code has five major methods:
-	Algorithm1
-	Algorithm1_c
-	Algorithm2
-	Algorithm2_modified
-	Algorithm3

We were able to fully implements all 4 algorithms, but we started with Algorithm1 because Algorithm1_c is for file I/O, which we considered a good starting point. Additionally Algorithm2 and Algorithm2_modified provided the same output, making the modified version initially optional. We found the difference is that Algorithm2_modified offers a more efficient version and saves memory. Our program allows users to change between these two methods. Algorithm_3 uses an expansionTree to track the parentNodes which further saves memory. A programmaticall call to query.isTree(int SubgraphSize) enables the to determination of whether to use Algorithm2 or Algorithm3.

## Data
To test comparable results, our program uses the same dataset (SampleInputGraph.txt) as the original program. Alternate tests may be ran by changing the path given to “argsStr” in Main. The input data must contain a tab separated list of nodes and edges. Our goal was to ensure accuracy above efficiency, trusting that the algorithm would work with minimal operational differences. 

The C# ParaMODA implementation used json to store some data. For our implementation we found a open source json library for C++ for this. https://github.com/nlohmann/json

Figure 1 and 2 demonstrate our sample input for a size 5 graph: 
![image](https://user-images.githubusercontent.com/36549707/119889626-0b8cb300-bef4-11eb-8582-009f14887a58.png)
![image](https://user-images.githubusercontent.com/36549707/119889715-2b23db80-bef4-11eb-8e16-d423ac6df0ec.png)

## Testing and Results
We compared the results of the original program to our own. Figure 3 shows the output of the original ParaMODA in C# with a size 5 graph on a Lenovo ThinkPad Yoga 260 with Windows 10 and using Visual Studio 2017: 
![image](https://user-images.githubusercontent.com/36549707/119890269-db91df80-bef4-11eb-90b5-a13cf5d9f529.png)
 
Our project includes a “makefile” which simplified the testing process. To test our implementation in a Linux command line, from the files directory enter “make all” which will run the program. We initially programmed and tested in a Mac Unix environment. Final testing was done on the UWB servers which required us to make some alterations to the “makefile”. In figure 4, we show the test output from our ParaMODA in C++ of a size 4 and size 5 graph
![image](https://user-images.githubusercontent.com/36549707/119890324-ec425580-bef4-11eb-909e-0fbbfbf00ff0.png) 
![image](https://user-images.githubusercontent.com/36549707/119890361-f9f7db00-bef4-11eb-9786-8917723e98e2.png)
 
After testing our output, we consistently got wrong results. We believe the problem lies in the file Utils.cpp under IsomorphicExtension. 

## Conclusion 
ParaMODA is a complex program with a lot of interdependencies. This project proved more challenging than we had originally expected. Unlike typical undergraduate work, there wasn’t very much information to pull from when trying to overcome some of our obstacles. Building this project was not just for the grades but more importantly, it is for the whole experience. First thing we learned is the work distribution and communication. A good distribution of work and active working atmosphere make our building progress more efficiently. After the project we understand some basic building application steps. For our project:
- Understanding how network motif are found
- Understanding ParaMODA Algorithms 
- Translating c# into c++(finding a way to deal with syntax difference)
- Check syntax, dependencies and other errors
- Memory leaks
- Building and running the final product <br/>
These experiences are valuable to us and benefits us once we go to workplace with large projects.

## Future Works
Due to timing restrictions, these are the things that should be continued. The Utils.IsomorphicExtension returns incorrect output which in storing the mapping into a queryGraph. More work will need to be done to ensure an correct output. All output is also limited to the command line. A Graphic User Interface would greatly improve the usability of our project. We’ve also considered investigating the possibility of implementing it as a website which would broaden the usability in an area that does not currently exist. The feasibility of such an implementation and reliable user access is unknown at this moment.

## Works Cited

Mbadiwe, Somadina, and Wooyoung Kim. “ParaMODA: Improving Motif-Centric Subgraph Pattern Search in PPI Networks.” 2017 IEEE International Conference on Bioinformatics and Biomedicine (BIBM), 2017, doi:10.1109/bibm.2017.8217920.

“Smbadiwe/ParaMODA.” GitHub, github.com/smbadiwe/ParaMODA.


