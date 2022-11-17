#pragma once
#include <vector>

class Simulation;

class Coalition {
public:
    Coalition(int id, int partyId, int agentId);
    int getCoalitionId() const;
    void addParty(int partyId);
    int getMandates(Simulation &s) const;
    int getOriginalAgentId() const;
    std::vector<int> getParties() const;
    bool isPartyInCoalition(int partyId) const;

private:
    int mCoalitionId;
    std::vector<int> mPartiesId;
    int mOriginalAgentId;
};
