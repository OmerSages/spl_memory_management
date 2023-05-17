#pragma once

#include <vector>
#include "Graph.h"

class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    
    int getCoalitionId() const;
    void setPartyId(int newId);
    void setAgentId(int newId);

    //rule of 5
    virtual ~Agent(); //destructor
    Agent(const Agent& other); //copy constractur
    Agent(Agent&& other); //move constructor
    Agent& operator=(const Agent& other); //copy assignemt operator
    Agent& operator=(Agent&& other); //move assignemt operator

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;

    int mCoalitionId;
};
