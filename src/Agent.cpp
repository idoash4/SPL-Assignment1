#include "Agent.h"
#include "SelectionPolicy.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    vector<int> partiesWithoutOffer;
    for (int partyId : sim.getGraph().GetNeighbors(mPartyId)) {
        const Party &party = sim.getParty(partyId);
        if (!party.hasOffer(mAgentId) and party.getState() != State::Joined) {
            partiesWithoutOffer.push_back(partyId);
        }
    }
    if(partiesWithoutOffer.size() != 0) {
        sim.offerParty(mSelectionPolicy->select(sim, mPartyId, partiesWithoutOffer), mAgentId);
    }
}

const SelectionPolicy &Agent::getSelectionPolicy() const {
    return *mSelectionPolicy;
}

Agent::~Agent() {
    //delete mSelectionPolicy;
}
