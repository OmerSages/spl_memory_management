#pragma once
#include <vector>
#include "Party.h"

using std::vector;

class Graph
{
public:
    Graph(vector<Party> vertices, vector<vector<int>> edges);
    int getMandates(int partyId) const;
    int getEdgeWeight(int v1, int v2) const;
    int getNumVertices() const;
    const Party &getParty(int partyId) const;

    Party& getAccessibleParty(int partyId);      // return a non const party reference
    void initializePartyOffersVector(int size);  // access each party to initiate it's "didOffer" vector

private:
    vector<Party> mVertices;
    vector<vector<int>> mEdges;
};
