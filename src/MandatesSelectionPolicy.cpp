#include "SelectionPolicy.h"
#include "Graph.h"
#include "Agent.h"

int MandatesSelectionPolicy::select(const Graph& graph, const Agent& agent)
{
    int max = -1;
    int selected = -1;
    
    for(int i=0; i<graph.getNumVertices(); i++)
    {
        if(graph.getEdgeWeight(agent.getPartyId(),i) > 0) //check if neighbor
        {
            const Party &curParty = graph.getParty(i);
            //check if the party is not in join state and has'nt alredy recieved an offer from the coalition
            if((curParty.getState() != Joined) && (! curParty.hasOffer(agent.getCoalitionId())))
            {
                int mandates = curParty.getMandates();
                if(mandates>max)
                {
                    max = mandates;
                    selected = i;
                }
            }              
        }
    }

    return selected;     
}

SelectionPolicy* MandatesSelectionPolicy::clone()
{
    return new MandatesSelectionPolicy;
}