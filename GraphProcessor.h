#ifndef __GRAPH_PROCESSOR_H
#define __GRAPH_PROCESSOR_H

namespace GraphProcessor
{
	template<class T>
	inline string LoadGraph(string filename, UndirectedGraph<T> *newGraphInstance)
	{
		vector<string> lines;
		
		string line;
		ifstream inFile (filename);
		if (inFile.is_open())
		{
			while ( getline (inFile,line) )
			{
				lines.push_back(line);
			}
			inFile.close();
		}; 
		
		vector<string> tmp;		
		T temp_node;
		T temp_node2;
		
		for(auto & line : lines)
		{
			if(line.at(0) == '#')
			{
				continue;
			}
			tmp = 
			// if (line.StartsWith("#")) continue;
            //     tmp = line.Split(new string[] { " ", "\t" }, StringSplitOptions.None);
            //     temp_node = (T)Convert.ChangeType(tmp[0], typeof(T));
            //     temp_node2 = (T)Convert.ChangeType(tmp[1], typeof(T));
			// 
            //     newGraphInstance.AddVerticesAndEdge(new Edge<T>(temp_node, temp_node2));
		}
		return "0";
	}
	
	UndirectedGraph<int> LoadGraph(std::string filename, bool isQueryGraph = false);
}

#endif
