#include "JoinPolicy.h"
#include "Party.h"
#include "Simulation.h"
#include <vector>

using std::vector;

// class Party;
// class Simulation;

int MandatesJoinPolicy::join(const Party& party, const Simulation& sim)
{
    int selected = -1;
    int max = -1;
    vector<int> offers = party.getOffersVector();
    vector<int> cMandates = sim.getCoalitionMandates();
    
    for(unsigned int i=0; i<offers.size(); i++)
    {
        if(offers[i]!=-1)
        {
            if(cMandates[i] == max && offers[i]<offers[selected])
            {
                selected = i;
            }
            if(cMandates[i]>max)
            {
                max = cMandates[i];
                selected = i;
            }
        }
    }

    return selected;
    
}

JoinPolicy* MandatesJoinPolicy::clone()
{
    return new MandatesJoinPolicy;
}
