#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"
#include "Coalition.h"

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
    void acceptCoalitionOffer(int partyId, int coalitionId);
    const Coalition& getCoalition(int coalitionId) const;
    const Coalition& getCoalitionByParty(int partyId) const;
    void offerParty(int partyId, int coalitionId);

private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition> mCoalitions;
    static const int MANDATES_NEEDED = 61;
};
