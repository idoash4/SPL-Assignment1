#pragma once
#include <vector>
#include <string>

using std::string;

class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    const bool hasOffer(int agentId) const;
    void offer(int agentId);

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int mStepsTimer;
    static const int MAX_STEPS_TIMER = 3;
    std::vector<int> mAgentIdOffers;
};
