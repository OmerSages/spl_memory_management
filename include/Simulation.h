#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"

using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;

    Graph& getAccessibleGraph();   //returns a non const reference to the graph
    const vector<int>& getCoalitionMandates() const;
    void addPartyToCoalition(int cId, Party& party);

private:
    Graph mGraph;
    vector<Agent> mAgents;

    vector<vector<int>> sCoalitions;
    vector<int> coalitionsMandates; //holds the total mandets number of each coalition
    bool foundSolution; //true if there is a coalition with over 60 mandates
    int partiesOutOfCoalition; //updets accurent to the number of party that don't form part of any coalition
};
