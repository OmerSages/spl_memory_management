#include "SelectionPolicy.h"
#include "Graph.h"
#include "Agent.h"

int EdgeWeightSelectionPolicy::select(const Graph& graph, const Agent& agent)
{
    int max = -1;
    int selected = -1;
    
    for(int i=0; i<graph.getNumVertices(); i++) //run over each party
    {
        int weight = graph.getEdgeWeight(agent.getPartyId(),i);
        if(weight > 0) //check if neighbor
        {
            const Party &curParty = graph.getParty(i); 
            //check if the party is not in join state and has'nt alredy recieved an offer from the coalition
            if((curParty.getState() != Joined) && (! curParty.hasOffer(agent.getCoalitionId())))
            {
                if(weight>max)
                {
                    max = weight;
                    selected = i;
                }
            }              
        }
    }
    return selected;               
}

SelectionPolicy* EdgeWeightSelectionPolicy::clone()
{
    return new EdgeWeightSelectionPolicy;
}
