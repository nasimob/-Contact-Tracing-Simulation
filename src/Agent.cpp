#include "../include/Agent.h"
#include <vector>
#include <queue>
using namespace std;

Agent::Agent() = default;

Agent::~Agent()  = default;


//=============Virus=============

//constructor
Virus::Virus(int nodeInd):nodeInd(nodeInd) {

}
//clone
Agent* Virus::clone() const {
    return new Virus(*this);
}

void Virus::act(Session& session){
    session.enqueueInfected(nodeInd);
    Graph graph = session.get_graph();
    vector<vector<int>> edges = graph.get_edges();
    for(size_t i=0; i<edges[nodeInd].size(); i++){ //todo unsigned vs signed
        if((edges[nodeInd][i] == 1) && (!graph.isInfected(i)) && !session.check_virus(i)){
            Agent* virus = new Virus(i);
            session.addAgent(*virus);
            delete virus;
            virus = nullptr; //todo check
            break;
        }
    }
}
int Virus::getnode() {
    return nodeInd;
}
//=============ContactTracer=============

//constructor
ContactTracer::ContactTracer() {}

void ContactTracer::act(Session &session) {

    if(! session.get_infection_queue().empty()){
        int infected_node = session.dequeueInfected(); //front() and pop()
        Graph g = session.get_graph();
        vector<bool> visted_child(g.get_edges().size()) ;
        Tree *tree = g.BFS(infected_node,session,visted_child);
        g.disconnect_node(tree->traceTree());
        delete tree;
        tree = nullptr;
        session.setGraph(g);
    }
}

Agent* ContactTracer::clone() const {
    return new ContactTracer(*this);
}

int ContactTracer::getnode() {
    return -1;
}
