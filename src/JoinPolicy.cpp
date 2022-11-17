#include "JoinPolicy.h"
#include "Simulation.h"

int MandatesJoinPolicy::select(Simulation &s, const std::vector<int> &agentIdOffers) {
    int maxMandate = 0;
    int maxAgentMandateOffer = -1;
    for (int agentId : agentIdOffers) {
        const Coalition& coalition = s.getCoalitionByAgent(agentId);
        if (maxMandate < coalition.getMandates(s)) {
            maxMandate = coalition.getMandates(s);
            maxAgentMandateOffer = agentId;
        }
    }
    return maxAgentMandateOffer;
}

MandatesJoinPolicy *MandatesJoinPolicy::clone() const {
    return new MandatesJoinPolicy(*this);
}

int LastOfferJoinPolicy::select(Simulation &s, const std::vector<int> &agentIdOffers) {
    return agentIdOffers.back();
}

LastOfferJoinPolicy *LastOfferJoinPolicy::clone() const{
    return new LastOfferJoinPolicy(*this);
}