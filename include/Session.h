#ifndef SESSION_H_
#define SESSION_H_

#include <queue>
#include <vector>
#include <string>
#include "../include/Graph.h"
#include "../include/Tree.h"
#include "../include/Agent.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"
using json = nlohmann::json;

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    //constructor
    Session(const std::string& path);
    //copy constructor
    Session(const Session &other);
    //move constructor
     Session(Session &&other);
    //copy assignment operator
    const Session &operator=(const Session &other);
    //move assignment operator
    const Session &operator=(Session &&other);
    //destructor
    ~Session();

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    //==========functions to add==========
    int get_cycle() const ; //used in Tree Class creatTree()
    bool isInfected(int);
    std::queue<int> get_infection_queue()  ;
    Graph get_graph(); //used in Agent Class act()
    std::vector<std::vector<int>> get_edges(); //used in Agent Class act()
    bool terminate();
    void tostring();
    bool check_virus(int);

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    // =======fields to add=======
    std::queue<int> infected_nodes;
    int currCycle;

};
#endif
