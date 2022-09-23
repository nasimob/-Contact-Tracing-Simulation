#include "../include/Session.h"
#include <string>
#include <vector>
#include <queue>
#include <iostream>
using json = nlohmann::json;
using namespace std;
//constructor
Session::Session(const string &Path) :g({}),treeType(),agents(),infected_nodes(),currCycle(0) {
    ifstream i(Path);
    json j;
    i >> j;
    for (pair<string, int> a: j["agents"]) {
        if (a.first == "V"){
            Agent* virus_add = new Virus(a.second);
            addAgent(*virus_add);
            delete virus_add;
            virus_add =nullptr;//todo check
        }
        else{
            Agent* contact_tracer = new ContactTracer();
            addAgent(*contact_tracer);
            delete contact_tracer;
            contact_tracer = nullptr;//todo check
        }
    }
        vector<vector<int>> matrix {j["graph"].size()};
    for(size_t t = 0 ; t < j["graph"].size() ; ++t){
        for(size_t k = 0 ; k < j["graph"].size() ; ++k){
            int value = j["graph"][t][k];
            matrix[t].push_back(value);
        }
    }
    g = Graph(matrix);
    if (j["tree"] == "M") {
        treeType = MaxRank;
    }
    if (j["tree"] == "R") {
        treeType = Root;
    } if(j["tree"] == "C"){
        treeType = Cycle;
    }
    i.close();
}
//destructor
Session::~Session() {
    for(auto &agent:agents){
        if(agent != nullptr){
             delete agent;
             agent = nullptr;
        }
    agents.clear();
 }
}
//copy constructor
Session::Session(const Session &other): g(other.g),treeType(other.treeType),agents(),infected_nodes(other.infected_nodes),currCycle(other.currCycle) {
    for(auto * x : other.agents)
        agents.push_back(x->clone()); // *x->clone()



}
//move constructor
 Session::Session(Session &&other):g(other.g),treeType(other.treeType),agents(other.agents),infected_nodes(other.infected_nodes),currCycle(other.currCycle){
    if(!other.g.get_edges().empty()){
        for(unsigned i = 0; i < other.g.get_edges().size() ; ++i){
            for(unsigned j = 0; j < other.g.get_edges()[i].size() ; ++j) {
                g.get_edges()[i][j] = other.g.get_edges()[i][j];
            }
        }
    }
        for (auto *x: other.agents)
            agents.push_back(x);
}

//copy assignment operator
const Session & Session::operator=(const Session &other) {
    if(this == &other){
        return *this;
    }
    for(auto  * i : agents)
        delete i ;
    this->g = other.g;
    for (auto *x: other.agents)
    agents.push_back(x);
    return *this;
}

//move assignment operator
const Session & Session::operator=(Session &&other) {
    if(this == &other){
        return *this;
    }
    for(auto *i: agents)
        delete i;

    for(auto *i : other.agents)
        agents.push_back(i);
    g = other.g;
    treeType = other.treeType;
    return *this;
}

void Session::tostring() {
 for(size_t i =0; i < g.get_edges().size() ; ++i){
     cout << i << " is " << g.isInfected(i) <<endl;
     for(size_t j =0; j < g.get_edges().size() ; ++j){
         cout << g.get_edges().at(i).at(j) << " ";
     }
     cout << endl;
 }

}

void Session::simulate() {
    while (!terminate()) {
        int size = agents.size();
        for (int i = 0; i < size; ++i) {
            agents.at(i)->act(*this);
        }
        currCycle += 1;
    }
    tostring();
}

bool Session::terminate(){ //todo check the output is wrong

    for( size_t i=0; i<g.get_edges().size() ; i++){
        for( size_t j=0 ; j<g.get_edges().size() ; j++){
            if(((g.get_edges()[i][j] == 1) && !(g.isInfected(i)) && (g.isInfected(j))) ||((g.get_edges()[i][j] == 1) && (g.isInfected(i)) && !(g.isInfected(j)))){
                return false;
            }
        }
    }
    for(unsigned int i=0; i<agents.size() ; i++){
        if((agents[i]->getnode() != -1) && (!g.isInfected(agents[i]->getnode()))){
            return false;
        }
    }
    return true;
}

void Session::addAgent(const Agent& agent) {
    Agent *clone = agent.clone();
    agents.push_back(clone);
}

TreeType Session::getTreeType() const {
    return treeType;
}
void Session::setGraph(const Graph &graph) { //todo check
    g = graph;
}
int Session::dequeueInfected() {
    int infected_node = infected_nodes.front();
    infected_nodes.pop();
    return infected_node;
}
void Session::enqueueInfected(int nodeInd) {//todo get the if down 150<->151
        if(!g.isInfected(nodeInd)){
            infected_nodes.push(nodeInd);
           g.infectNode(nodeInd);
    }
}


// ==================== functions to add ====================


 int Session::get_cycle() const {
     return currCycle;
}

std::queue<int> Session::get_infection_queue() {
    return infected_nodes;
}

Graph Session::get_graph() {
    return  g;
}

std::vector<std::vector<int>> Session::get_edges() {
    return g.get_edges();
}


bool Session::isInfected(int nodeInd) {
    for(auto i:g.get_infected_list()){
        if(nodeInd == i)
            return true;
    }
    return false;
}

bool Session::check_virus(int node) {
    for(size_t i =0 ; i < agents.size() ; ++i){
        if(agents[i]->getnode() == node){
            return true;
        }
    }
    return false;
}