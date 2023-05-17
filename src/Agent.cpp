#include "Agent.h"
#include "Simulation.h"
#include "SelectionPolicy.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), mCoalitionId(agentId)
{
    // You can change the implementation of the constructor, but not the signature!
}

Agent::Agent(const Agent& other): mAgentId(other.mAgentId), mPartyId(other.mPartyId),mSelectionPolicy(other.mSelectionPolicy->clone()), mCoalitionId(other.mCoalitionId)
{
    //copy constructor
}

Agent::Agent(Agent&& other): mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy), mCoalitionId(other.mCoalitionId) 
{
    //move constructor
    other.mSelectionPolicy = nullptr;
}

Agent::~Agent()
{
    //destructor
    if(mSelectionPolicy)
        delete mSelectionPolicy;
}

Agent& Agent::operator=(const Agent& other)
{
    //copy assignment operator
    if(this != &other)
    {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mCoalitionId = other.mCoalitionId;

        if(mSelectionPolicy)
        {
            delete mSelectionPolicy;
        }
        mSelectionPolicy = other.mSelectionPolicy->clone();
    }
    return *this;
}

Agent& Agent::operator=(Agent&& other)
{
    //move assignment operator
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    mCoalitionId = other.mCoalitionId;

    if(mSelectionPolicy)
    {
        delete mSelectionPolicy;
    }
    mSelectionPolicy = other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;

    return *this;
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}
int Agent::getCoalitionId() const
{
    return mCoalitionId;
}

void Agent::setPartyId(int newId)
{
    mPartyId = newId;
}
void Agent::setAgentId(int newId)
{
    mAgentId = newId;
}

void Agent::step(Simulation &sim)
{
    int selected = mSelectionPolicy->select(sim.getGraph(),*this); //select party to offer
    if(selected != -1)
        sim.getAccessibleGraph().getAccessibleParty(selected).collectOffer(mCoalitionId); //party colects the offer
}
