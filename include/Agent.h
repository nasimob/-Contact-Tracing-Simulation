#ifndef AGENT_H_
#define AGENT_H_
#include <vector>
#include "Session.h"
//#include "../include/Tree.h"



class Agent{
public:
    Agent();
    virtual void act(Session &session)=0;
    virtual Agent* clone() const = 0 ;
    virtual ~Agent() ;
    //======method to add======
    virtual int getnode() =0;
};
//=======================================
class ContactTracer: public Agent{
public:
    ContactTracer();
    Agent* clone() const;
    virtual void act(Session& session);
     virtual int getnode()  ;
};
//=======================================
class Virus: public Agent{
public:
    Virus(int nodeInd);
    Agent* clone() const;
    virtual void act(Session& session);
     virtual int getnode() ;
    //==========method to add==========

private:
    const int nodeInd;

};
#endif
