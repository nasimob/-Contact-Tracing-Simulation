#include "../include/Graph.h"
#include "../include/Session.h"
#include <vector>
#include <queue>


using namespace std;
Graph::Graph(vector<vector<int>> matrix): edges(matrix.size()), infected_nodes()  {
    edges = matrix;
}

void Graph::infectNode(int nodeInd) { // there is need to check if the node is already infected ?
  infected_nodes.push_back(nodeInd);
}

bool Graph::isInfected(int nodeInd) {
    for (auto i: infected_nodes) {
        if (i == nodeInd)
            return true;
    }
    return false;
}

vector<vector<int> > Graph::get_edges() {
  return edges;
}

 Tree* Graph::BFS(int infected_node ,Session session , vector<bool> & visted_child ) { //todo check
     queue<Tree*> trees_counter;
     Tree* infected = Tree::createTree(session,infected_node);
     trees_counter.push(infected);
     visted_child[infected_node] = true;
         while(!trees_counter.empty()) {
             for (size_t i = 0; i < edges.size(); ++i) {
                 if (edges[trees_counter.front()->getnode()][i] == 1 && !visted_child[i]) {
                    trees_counter.front()->getchildren().push_back(Tree::createTree(session,i));
                    visted_child[i] = true;
                 }
             }
             for(size_t i =0; i < trees_counter.front()->getchildren().size() ; ++i){
                 trees_counter.push(trees_counter.front()->getchildren().at(i));
             }
             trees_counter.pop();
         }
     return infected;
}

std::vector<int> Graph::get_infected_list() {
    return infected_nodes;
}

void Graph::disconnect_node(int node_label) {
    for(unsigned i =0; i < edges.size(); ++i){
        edges[node_label][i] = 0;
        edges[i][node_label] = 0;
    }
}

