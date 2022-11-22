#include "Coalition.h"
#include "Simulation.h"
#include <algorithm>

Coalition::Coalition(int id, const Party& party, int agentId) : mCoalitionId(id), mPartiesId(), mOriginalAgentId(agentId), mMandates(party.getMandates())
{
    mPartiesId.push_back(party.getId());
}

int Coalition::getCoalitionId() const
{
    return mCoalitionId;
}

int Coalition::getMandates() const
{
    return mMandates;
}

void Coalition::addParty(const Party& party)
{
    mPartiesId.push_back(party.getId());
    mMandates += party.getMandates();
}

std::vector<int> Coalition::getParties() const {
    return mPartiesId;
}

int Coalition::getOriginalAgentId() const {
    return mOriginalAgentId;
}

bool Coalition::isPartyInCoalition(int partyId) const {
    return std::find(mPartiesId.begin(), mPartiesId.end(), partyId) != mPartiesId.end();
}
