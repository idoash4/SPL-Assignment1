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
    void step(Simulation &s);
    const Party &getParty(int partyId) const;
    std::vector<int> getNeighbors(int partyId) const;
    void offerParty(int partyId, int agentId);
    bool hasAllJoined() const;

private:
    vector<Party> mVertices;
    vector<vector<int>> mEdges;
};
