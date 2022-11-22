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
    ~Party();
    Party(const Party& other);
    Party& operator=(const Party& other);
    Party(Party&& other) noexcept;
    Party& operator=(Party&& other);
    int getId() const;
    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    bool hasOffer(int coalitionId) const;
    void offer(int coalitionId);

private:
    int mId;
    string mName;
    int mMandates;
    State mState;
    int mStepsTimer;
    static const int MAX_STEPS_TIMER = 3;
    std::vector<int> mCoalitionOffers;
    JoinPolicy *mJoinPolicy;
};
