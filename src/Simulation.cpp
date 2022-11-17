#include "Simulation.h"
#include "SelectionPolicy.h"
#include <stdexcept>

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), mCoalitions()
{
    for (unsigned int i = 0; i < agents.size(); ++i) {
        mCoalitions.emplace_back(i, agents[i].getPartyId(), agents[i].getId());
    }
}

void Simulation::step()
{
    mGraph.step(*this);
    for (Agent& agent : mAgents) {
        agent.step(*this);
    }
}

bool Simulation::shouldTerminate() const
{
    for (const Coalition &coalition : mCoalitions) {
        if (coalition.getMandates(const_cast<Simulation &>(*this)) >= MANDATES_NEEDED) {
            return true;
        }
    }
    return mGraph.hasAllJoined();
}

const Graph& Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent>& Simulation::getAgents() const
{
    return mAgents;
}

const Party& Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

const Coalition& Simulation::getCoalition(int coalitionId) const
{
    return mCoalitions[coalitionId];
}

void Simulation::acceptCoalitionOffer(int partyId, int coalitionId)
{
    const Coalition& coalition = getCoalition(coalitionId);
    mCoalitions[coalition.getCoalitionId()].addParty(partyId);
    int newAgentId = mAgents.size();
    mAgents.emplace_back(newAgentId, partyId, mAgents[coalition.getOriginalAgentId()].getSelectionPolicy().clone());
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> coalitions;
    for (const Coalition &coalition : mCoalitions) {
        coalitions.push_back(coalition.getParties());
    }
    return coalitions;
}

void Simulation::offerParty(int partyId, int coalitionId) {
    mGraph.offerParty(partyId, coalitionId);
}

const Coalition &Simulation::getCoalitionByParty(int partyId) const {
    for (const Coalition& coalition : mCoalitions) {
        if (coalition.isPartyInCoalition(partyId)) {
            return coalition;
            }
        }
    throw std::invalid_argument("Received invalid party id (not in coalition)");
}
