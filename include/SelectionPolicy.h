#pragma once
#include "Simulation.h"

class SelectionPolicy {
public:
    virtual ~SelectionPolicy() = default;
    virtual SelectionPolicy* clone() const = 0;
    virtual int select(Simulation &s, int agentId, const std::vector<int>& partiesId) = 0;
};

class MandatesSelectionPolicy: public SelectionPolicy{
    MandatesSelectionPolicy* clone() const;
    virtual int select(Simulation &s, int sourcePartyId, const std::vector<int>& partiesId);
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
    EdgeWeightSelectionPolicy* clone() const;
    virtual int select(Simulation &s, int sourcePartyId, const std::vector<int>& partiesId);
};
