#pragma once
#include <vector>
#include "Simulation.h"

class JoinPolicy {
public:
    virtual ~JoinPolicy() = default;
    virtual JoinPolicy* clone() const = 0;
    virtual int select(Simulation &s, const std::vector<int> &agentIdOffers) = 0;
};

class MandatesJoinPolicy : public JoinPolicy {
public:
    MandatesJoinPolicy* clone() const;
    int select(Simulation &s, const std::vector<int> &agentIdOffers);
};

class LastOfferJoinPolicy : public JoinPolicy {
public:
    LastOfferJoinPolicy* clone() const;
    int select(Simulation &s, const std::vector<int> &agentIdOffers);
};