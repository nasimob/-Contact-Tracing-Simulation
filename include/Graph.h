#ifndef GRAPH_H_
#define GRAPH_H_
#include <queue>
#include <vector>
#include "../include/Tree.h"
#include <iostream>


class Graph{
public:
    // creat graph with the given adjacency matrix
    Graph(std::vector<std::vector<int>> matrix);
    //adds the given infected node index to the infected list
    void infectNode(int nodeInd);
    //return true if the node is infected, else false
    bool isInfected(int nodeInd);
    //==========methods to add============
    //return edges field
    std::vector<std::vector<int>> get_edges();
    //return infected_list
    std::vector<int> get_infected_list();
    //BFS return Tree pointer
     Tree* BFS (int, Session, std::vector<bool>&);

    void disconnect_node(int);
    //==========methods to add============



private:
    std::vector<std::vector<int>> edges;
    //=====fields to add=====
    std::vector<int> infected_nodes;

};
#endif
