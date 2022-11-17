#include "Party.h"
#include "JoinPolicy.h"
#include <algorithm>

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mState(Waiting), mStepsTimer(0), mCoalitionOffers(), mJoinPolicy(jp)
{
    // You can change the implementation of the constructor, but not the signature!
}

Party::~Party()
{
    delete mJoinPolicy;
}

Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mState(other.mState), mStepsTimer(other.mStepsTimer), mCoalitionOffers(other.mCoalitionOffers), mJoinPolicy(
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
        this->mCoalitionOffers = other.mCoalitionOffers;
        delete mJoinPolicy;
        this->mJoinPolicy = other.mJoinPolicy->clone();
    }
    return *this;
}

Party::Party(Party &&other) noexcept : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mState(other.mState), mStepsTimer(other.mStepsTimer), mCoalitionOffers(other.mCoalitionOffers), mJoinPolicy(other.mJoinPolicy)
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
    this->mCoalitionOffers = other.mCoalitionOffers;
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
        case State::Joined:
            break; // We don't need to do anything in Waiting and Joined states
        case State::CollectingOffers:
            if (mStepsTimer == Party::MAX_STEPS_TIMER) {
                // We reached the end of the timer, time to choose an offer
                int selected_coalition_id = mJoinPolicy->select(s, mCoalitionOffers);
                s.acceptCoalitionOffer(mId, selected_coalition_id);
                mState=State::Joined;
            } else {
                // Increase the timer by 1
                mStepsTimer++;
            }
    }
}

bool Party::hasOffer(int coalitionId) const {
    return std::find(mCoalitionOffers.begin(), mCoalitionOffers.end(), coalitionId) != mCoalitionOffers.end();
}

void Party::offer(int coalitionId) {
    mCoalitionOffers.push_back(coalitionId);
    if (mState == State::Waiting) {
        mState = State::CollectingOffers;
        mStepsTimer++;
    }
}
