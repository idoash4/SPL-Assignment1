#include "Graph.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{
    // You can change the implementation of the constructor, but not the signature!
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

std::vector<int> Graph::getNeighbors(int partyId) const
{
    vector<int> neighbors;
    for (unsigned int i = 0; i < mEdges[partyId].size(); ++i) {
        if (mEdges[partyId][i] != 0) {
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}

void Graph::step(Simulation& s)
{
    for (Party& party : mVertices) {
        party.step(s);
    }
}

void Graph::offerParty(int partyId, int agentId) {
    mVertices[partyId].offer(agentId);
}

bool Graph::hasAllJoined() const {
    for (const Party& party : mVertices) {
        if (party.getState() != State::Joined) {
            return false;
        }
    }
    return true;
}
