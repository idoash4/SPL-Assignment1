#include "SelectionPolicy.h"

int MandatesSelectionPolicy::select(Simulation &s, int sourcePartyId, const std::vector<int> &partiesId)
{
    int maxMandate = 0;
    int maxPartyMandate = -1;
    for (int partyId : partiesId) {
        const Party& party = s.getParty(partyId);
        if (maxMandate < party.getMandates()) {
            maxMandate = party.getMandates();
            maxPartyMandate = partyId;
        }
    }
    return maxPartyMandate;
}

MandatesSelectionPolicy* MandatesSelectionPolicy::clone() const
{
    return new MandatesSelectionPolicy(*this);
}

int EdgeWeightSelectionPolicy::select(Simulation &s, int sourcePartyId, const std::vector<int> &partiesId)
{
    int maxWeight = 0;
    int maxPartyWeight = -1;
    for (int partyId : partiesId) {
        const Party& party = s.getParty(partyId);
        int weight = s.getGraph().getEdgeWeight(partyId, sourcePartyId);
        if (maxWeight < weight) {
            maxWeight = weight;
            maxPartyWeight = partyId;
        }
    }
    return maxPartyWeight;
}

EdgeWeightSelectionPolicy* EdgeWeightSelectionPolicy::clone() const
{
    return new EdgeWeightSelectionPolicy(*this);
}