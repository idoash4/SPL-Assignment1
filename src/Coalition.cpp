#include "Coalition.h"
#include "Simulation.h"
#include <algorithm>

Coalition::Coalition(int id, int partyId, int agentId) : mCoalitionId(id), mPartiesId(), mOriginalAgentId(agentId)
{
    mPartiesId.push_back(partyId);
}

int Coalition::getCoalitionId() const
{
    return mCoalitionId;
}

int Coalition::getMandates(Simulation &s) const
{
    int mandates = 0;
    for (int partyId : mPartiesId) {
        mandates += s.getParty(partyId).getMandates();
    }
    return mandates;
}

void Coalition::addParty(int partyId)
{
    mPartiesId.push_back(partyId);
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
