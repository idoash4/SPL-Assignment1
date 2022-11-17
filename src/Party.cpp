#include "Party.h"
#include "JoinPolicy.h"
#include <algorithm>

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mState(Waiting), mStepsTimer(0), mAgentIdOffers(), mJoinPolicy(jp)
{
    // You can change the implementation of the constructor, but not the signature!
}

Party::~Party()
{
    delete mJoinPolicy;
}

Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mState(other.mState), mStepsTimer(other.mStepsTimer), mAgentIdOffers(other.mAgentIdOffers), mJoinPolicy(
        nullptr)
{
    this->mJoinPolicy = other.mJoinPolicy->clone();
}

Party &Party::operator=(const Party &other)
{
    if (this != &other) {
        this->mId = other.mId;
        this->mName = other.mName;
        this->mMandates = other.mMandates;
        this->mState = other.mState;
        this->mStepsTimer = other.mStepsTimer;
        this->mAgentIdOffers = other.mAgentIdOffers;
        delete mJoinPolicy;
        this->mJoinPolicy = other.mJoinPolicy->clone();
    }
    return *this;
}

Party::Party(Party &&other) noexcept : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mState(other.mState), mStepsTimer(other.mStepsTimer), mAgentIdOffers(other.mAgentIdOffers), mJoinPolicy(other.mJoinPolicy)
{
    other.mJoinPolicy = nullptr;
}

Party& Party::operator=(Party &&other)
{
    this->mId = other.mId;
    this->mName = other.mName;
    this->mMandates = other.mMandates;
    this->mState = other.mState;
    this->mStepsTimer = other.mStepsTimer;
    this->mAgentIdOffers = other.mAgentIdOffers;
    delete mJoinPolicy;
    this->mJoinPolicy = other.mJoinPolicy->clone();
    return *this;
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string& Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    switch (mState) {
        case State::Waiting:
            return;
        case State::CollectingOffers:
            if (mStepsTimer == Party::MAX_STEPS_TIMER) {
                int selected_agent_id = mJoinPolicy->select(s, mAgentIdOffers);
                s.addPartyToCoalition(mId, selected_agent_id);
                mState=State::Joined;
            } else {
                mStepsTimer++;
            }
        case State::Joined:
            return;
    }
}

const bool Party::hasOffer(int agentId) const {
    return std::find(mAgentIdOffers.begin(), mAgentIdOffers.end(), agentId) != mAgentIdOffers.end();
}

void Party::offer(int agentId) {
    mAgentIdOffers.push_back(agentId);
    if (mState == State::Waiting) {
        mState = State::CollectingOffers;
        mStepsTimer++;
    }
}
