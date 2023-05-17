#include "JoinPolicy.h"
#include <vector>
#include "Party.h"

int LastOfferJoinPolicy::join(const Party& party, const Simulation& sim)
{
    int selected = -1;
    int max = -1;
    vector<int> offers = party.getOffersVector();
    
    for(unsigned int i=0; i<offers.size(); i++)
    {
        if(offers[i]>max)
        {
            max = offers[i];
            selected = i;
        }
    }

    return selected;
}

JoinPolicy* LastOfferJoinPolicy::clone()
{
    return new LastOfferJoinPolicy;
}
