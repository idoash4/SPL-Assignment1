#include "Agent.h"
#include "SelectionPolicy.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{

}

Agent::~Agent()
{
    delete mSelectionPolicy;
}

Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(nullptr)
{
    this->mSelectionPolicy = other.mSelectionPolicy->clone();
}

Agent& Agent::operator=(const Agent &other)
{
    if (this != &other) {
        this->mPartyId = other.mPartyId;
        this->mAgentId = other.mAgentId;
        delete mSelectionPolicy;
        this->mSelectionPolicy = other.mSelectionPolicy->clone();
    }
    return *this;
}

Agent::Agent(Agent&& other) noexcept : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy) {
    other.mSelectionPolicy = nullptr;
}

Agent& Agent::operator=(Agent &&other) {
    this->mAgentId = other.mAgentId;
    this->mPartyId = other.mPartyId;
    this->mSelectionPolicy = other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;
    return *this;
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
    for (int partyId : sim.getGraph().getNeighbors(mPartyId)) {
        const Party& party = sim.getParty(partyId);
        // TODO: The check should be for hasOffer for coalition not just an agent
        if (!party.hasOffer(mAgentId) and party.getState() != State::Joined) {
            partiesWithoutOffer.push_back(partyId);
        }
    }
    if(!partiesWithoutOffer.empty()) {
        sim.offerParty(mSelectionPolicy->select(sim, mPartyId, partiesWithoutOffer), mAgentId);
    }
}

const SelectionPolicy& Agent::getSelectionPolicy() const
{
    return *mSelectionPolicy;
}
