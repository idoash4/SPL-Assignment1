#pragma once
#include <vector>

class Simulation;

class Coalition {
public:
    Coalition(int id, int partyId, int agentId);
    const int getCoalitionId() const;
    void addAgent(int agentId);
    void addParty(int partyId);
    const bool isAgentInCoalition(int agentId) const;
    const int getMandates(Simulation &s) const;
    const std::vector<int> getParties() const;

private:
    int mCoalitionId;
    std::vector<int> mPartiesId;
    std::vector<int> mAgentsId;
};
