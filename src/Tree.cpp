#include "../include/Tree.h"
#include "../include/Session.h"

using namespace std;
//constructor
Tree::Tree(int rootLabel):node(rootLabel),children(){}
//copy constructor
Tree::Tree(Tree &other):node(other.node),children(other.children.size()) {
        for(auto *x : other.children)
            children.push_back(x->clone());
}
//destructor
 Tree::~Tree(){ //todo check
    for(size_t i=0 ; i < children.size() ; i++){
        delete children[i];
        children[i] = nullptr;
    }
}
//move constructor
Tree::Tree(Tree &&other):node(other.node),children(other.children.size()) {
    for(auto *i:other.children) {
        children.push_back(i);
    }
}
//copy assignment operator
const Tree &Tree::operator=(const Tree &other) {
    if(this == &other)
        return *this;

    for(auto  * i : children)
        delete i ;

    this->node = other.node;
    for(auto *i : other.children)
        children.push_back(i);
    return *this;
}
//move assignment operator
const Tree &Tree::operator=(Tree &&other) {
    if(this == &other)
        return *this;

    for(auto *i: children)
        delete i;

    for(auto *i : other.children)
        children.push_back(i);
    this->node = other.node;
    return *this;
}
//************************methods************************
int Tree::getnode() const {
    return node;
}

vector<Tree*>& Tree::getchildren() {
    return  children;
}

vector<Tree*> Tree::get_children() const { //used for clone const
    return children;
}

void Tree::setChildren(std::vector<Tree*> children){
    this->children = children;
}

//************************methods************************

void Tree::addChild(const Tree &child)  { //todo check
   children.push_back(child.clone());
}

Tree * Tree::createTree(const Session &session, int rootLabel) {
 TreeType type = session.getTreeType();
 Tree* tree_type;
    switch (type) {
        case Root:
            tree_type = new RootTree(rootLabel);
            break;
        case MaxRank:
            tree_type = new MaxRankTree(rootLabel);
            break;
        case Cycle:
            tree_type = new CycleTree(rootLabel,session.get_cycle()); //curr is const
            break;
    }
    return tree_type;
}

//==============================MaxRankTree==============================

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel){}
//destructor
MaxRankTree::~MaxRankTree() = default;

Tree* MaxRankTree::clone() const {
    Tree* rank = new MaxRankTree(this->getnode());
    vector<Tree*> children = this->get_children();
    vector<Tree*> newChildren;
    newChildren.reserve(children.size());
for(auto & i : children){
        newChildren.push_back(i->clone());
    }
    rank->setChildren(newChildren);
    return rank;
}

int MaxRankTree::traceTree() { //this algorithm considers the tie condition
     int node_return = this->getnode();
     int max_size = this->getchildren().size();
     queue<Tree*> que_node;
     que_node.push(this);
     while(!que_node.empty()){
         Tree* temp = que_node.front();
         que_node.pop();
         int temp_size = temp->getchildren().size();
         if(temp_size > max_size) {
             node_return = temp->getnode();
             max_size = temp->getchildren().size();
         }
         for(auto & i : temp->getchildren()){ //working with ascending order makes sure
             que_node.push(i);           // to consider all tie conditions !
         }
     }
     return node_return;
}

//==============================RootTree==============================

RootTree::RootTree(int rootLabel): Tree(rootLabel) {

}
//destructor
RootTree::~RootTree()= default;

Tree* RootTree::clone() const {
    Tree* root = new RootTree(this->getnode());
    vector<Tree*> children = this->get_children();
    vector<Tree*> newChildren;
    newChildren.reserve(children.size());
for(auto & i : children){
        newChildren.push_back(i->clone());
    }
    root->setChildren(newChildren);
    return root;
}

int RootTree::traceTree() {
    return this->getnode();
}

//==============================CycleTree==============================
CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){

}
//destructor
CycleTree::~CycleTree() = default;

int CycleTree:: get_curr_cycle() const{
    return currCycle ;
}

Tree* CycleTree::clone() const {
    Tree* cycle = new RootTree(this->getnode());
    vector<Tree*> children = this->get_children();
    vector<Tree*> newChildren;
    newChildren.reserve(children.size());
for(auto & i : children){
        newChildren.push_back(i->clone());
    }
    cycle->setChildren(newChildren);
    return cycle;
}

int CycleTree::traceTree() { //check the initialize value of curr_cycle1
    const Tree* t =this;
    for( int i=0; i<currCycle; ++i){
        vector<Tree*> children = t->get_children();
        if(!children.empty()){
            t = children[0];
        }
    }
    return t->getnode();
}
