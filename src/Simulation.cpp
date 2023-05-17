#include "Simulation.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), sCoalitions(), coalitionsMandates(), foundSolution(false), partiesOutOfCoalition(mGraph.getNumVertices() - mAgents.size()) 
{
    // You can change the implementation of the constructor, but not the signature!

    //Coalitions initialization
    for(Agent &agent: mAgents)
    {
        int partyId = agent.getPartyId();
        int partyMandates = getParty(partyId).getMandates();

        sCoalitions.push_back({partyId});
        coalitionsMandates.push_back(partyMandates);
        
        if(partyMandates>60)
            foundSolution = true;
    }
    
    mGraph.initializePartyOffersVector(mAgents.size());
    
}

void Simulation::step()
{
    //parties step
    for (int i=0; i < mGraph.getNumVertices(); i++)
        mGraph.getAccessibleParty(i).step(*this);
    //agents step
    for(Agent& agent: mAgents)
        agent.step(*this);       
}

bool Simulation::shouldTerminate() const
{   
    return ((partiesOutOfCoalition==0) | foundSolution) ;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

//return non const members
Graph& Simulation::getAccessibleGraph()
{
    return mGraph;
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    return  sCoalitions;
}

//return the vector holding coalitions corrent mandates
const vector<int>& Simulation::getCoalitionMandates() const
{
    return coalitionsMandates;
}

void Simulation::addPartyToCoalition(int cId, Party& party)
{
    //add the party to coalition matrix and update mandates
    sCoalitions[cId].push_back(party.getPartyId());
    coalitionsMandates[cId] += party.getMandates();

    //check if terminate needed
    if(coalitionsMandates[cId] > 60)
        foundSolution = true;
    partiesOutOfCoalition--;
    
    //clone agent
    Agent agentCloned = mAgents[cId]; //calls copy constructor
    agentCloned.setAgentId(mAgents.size());
    agentCloned.setPartyId(party.getPartyId());
    mAgents.push_back(agentCloned);

}


