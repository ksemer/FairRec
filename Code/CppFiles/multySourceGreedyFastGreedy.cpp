/**
 * This file contains a greedy algorithm to add edges to a graph in
 * order to maximize red pagerank ratio. It adds k edges to a single
 * source of the graph based on formula of the FairRec paper.
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cmath>
#include "graph.hpp"
#include "pagerank.hpp"
#include "edgeAddition.hpp"
#include <chrono>
#include <omp.h> 

int main()
{
    // Define number of threads to use.
    omp_set_num_threads(20);
    int numberOfSourceNodes = 20;
    int numberOfEdges = 20;
    int numberOfGraphNodes;

    std::ifstream inFile("out_graph.txt");
    std::string str;
    inFile >> str;
    inFile.close();

    numberOfGraphNodes = std::stoi(str);
    std::cout << "Number of nodes: " << str << std::endl;

    std::vector<int> sourceNodes = EdgeAddition::getRandomSourceNodes(numberOfSourceNodes, numberOfGraphNodes);

    EdgeAddition::getGreedyMultySource(sourceNodes, numberOfEdges);
    EdgeAddition::getFastGreedyMultySource(sourceNodes, numberOfEdges);

    return 0;
}
