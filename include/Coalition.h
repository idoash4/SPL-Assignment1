#pragma once
#include "Party.h"
#include <vector>

class Simulation;

class Coalition {
public:
    Coalition(int id, const Party& party, int agentId);
    int getCoalitionId() const;
    void addParty(const Party& party);
    int getMandates() const;
    int getOriginalAgentId() const;
    std::vector<int> getParties() const;
    bool isPartyInCoalition(int partyId) const;

private:
    int mCoalitionId;
    std::vector<int> mPartiesId;
    int mOriginalAgentId;
    int mMandates;
};
