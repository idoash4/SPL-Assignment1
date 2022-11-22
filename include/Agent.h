#pragma once

#include <vector>
#include "Graph.h"

class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    ~Agent();
    Agent(const Agent& other);
    Agent& operator=(const Agent& other);
    Agent(Agent&& other) noexcept;
    Agent& operator=(Agent&& other);
    int getPartyId() const;
    int getId() const;
    const SelectionPolicy& getSelectionPolicy() const;
    void step(Simulation &);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
};
