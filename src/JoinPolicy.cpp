#include "JoinPolicy.h"
#include "Simulation.h"

int MandatesJoinPolicy::select(Simulation &s, const std::vector<int>& coalitionIdOffers) {
    int maxMandate = 0;
    int maxCoalitionIdMandateOffer = -1;
    for (int coalitionId : coalitionIdOffers) {
        const Coalition& coalition = s.getCoalition(coalitionId);
        if (maxMandate < coalition.getMandates()) {
            maxMandate = coalition.getMandates();
            maxCoalitionIdMandateOffer = coalitionId;
        }
    }
    return maxCoalitionIdMandateOffer;
}

MandatesJoinPolicy *MandatesJoinPolicy::clone() const {
    return new MandatesJoinPolicy(*this);
}

int LastOfferJoinPolicy::select(Simulation &s, const std::vector<int>& coalitionIdOffers) {
    return coalitionIdOffers.back();
}

LastOfferJoinPolicy *LastOfferJoinPolicy::clone() const{
    return new LastOfferJoinPolicy(*this);
}