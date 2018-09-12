file=graph.cpp 001.GraphInit_Destroy.cpp 002.GraphHasEdge.cpp 003.GraphAddEdge.cpp 004.GraphPrint.cpp 005.GraphBFS.cpp 006.GraphPathPrint.cpp 007.GraphDFS.cpp
graph:$(file)
	g++ -g -o graph $(file)