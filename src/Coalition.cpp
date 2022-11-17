#include "Coalition.h"
#include "Simulation.h"
#include <algorithm>

Coalition::Coalition(int id, int partyId, int agentId) : mCoalitionId(id)
{
    mPartiesId.push_back(partyId);
    mAgentsId.push_back(agentId);
}

int const Coalition::getCoalitionId() const
{
    return mCoalitionId;
}

const int Coalition::getMandates(Simulation &s) const
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

void Coalition::addAgent(int agentId)
{
    mAgentsId.push_back(agentId);
}

const bool Coalition::isAgentInCoalition(int agentId) const
{
    return std::find(mAgentsId.begin(), mAgentsId.end(), agentId) != mAgentsId.end();
}

const std::vector<int> Coalition::getParties() const {
    return mPartiesId;
}
