#ifndef TREE_H_
#define TREE_H_
#include <vector>
//#include "Session.h"

class Session;

class Tree{
public:
    //Rule_Of_Five
    //constructor
    Tree(int rootLabel);
    //destructor
     virtual ~Tree();
    //copy constructor
    Tree(Tree &other) ;
    //move constructor
    Tree(Tree &&other);
    //copy assignment operator
    const Tree& operator=(const Tree &other);
    //move assignment operator
    const Tree& operator=(Tree &&other);



    void addChild( const Tree& child);

    static Tree* createTree(const Session& session, int rootLabel);

    virtual int traceTree()=0;
    //************************methods************************
    virtual  Tree* clone() const =0;

    virtual int getnode() const;

    virtual std::vector<Tree*>& getchildren() ;

    virtual  std::vector<Tree*> get_children() const; //used for clone const

    void setChildren(std::vector<Tree*> children);
    //************************methods************************
private:

    int node;
    std::vector<Tree*> children;


};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    //destructor
    virtual ~CycleTree();
    virtual int traceTree();
    //***********method***********
    virtual Tree* clone() const  ;
    int get_curr_cycle() const;
    //***********method***********
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree( int rootLabel);
    //destructor
    virtual ~MaxRankTree();
    virtual int traceTree();
    //***********method***********
    virtual Tree* clone() const ;
    //***********method***********

};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    //destructor
    virtual ~RootTree();
    virtual int traceTree();
    //***********method***********
    virtual Tree* clone() const ;
    //***********method***********
};
#endif
