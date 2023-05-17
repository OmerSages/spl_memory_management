#include "Party.h"
#include "JoinPolicy.h"
#include "Simulation.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), iterTimer(0), offersTimer(0), didOffer() 
{
    // You can change the implementation of the constructor, but not the signature! 
}

Party::Party(const Party& other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState), iterTimer(other.iterTimer),offersTimer(other.offersTimer), didOffer(other.didOffer)
{
    //copy constructor
}

Party::Party(Party&& other): mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), iterTimer(other.iterTimer),offersTimer(other.offersTimer), didOffer(std::move(other.didOffer))
{
    //move constructor
    other.mJoinPolicy = nullptr;
}

Party::~Party()
{
    //destructor
    if(mJoinPolicy)
        delete mJoinPolicy;
}

Party& Party::operator=(const Party& other)
{
    if(this != &other)
    {
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mState = other.mState;

        if(mJoinPolicy)   //delete the existsing policy then assign a new one according to other's policy type 
        {
            delete mJoinPolicy;
        }
        mJoinPolicy = other.mJoinPolicy->clone();

        iterTimer = other.iterTimer;
        offersTimer = other.offersTimer; 

        didOffer = other.didOffer;
    }

    return *this;
}

Party& Party::operator=(Party&& other)
{
    //move assignment operator

    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mState = other.mState;

    iterTimer = other.iterTimer;
    offersTimer = other.offersTimer; 

    didOffer = std::move(other.didOffer); //using Vector's move assignment operator

    if(mJoinPolicy)   //delete the existsing policy then assign a new one according to other's policy type 
    {
        delete mJoinPolicy;
    }
    mJoinPolicy = other.mJoinPolicy;
    other.mJoinPolicy = nullptr;

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

const string & Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    if(mState == CollectingOffers)
    {
        iterTimer++;
        if(iterTimer == 3)
        {
            int selected = mJoinPolicy->join(*this,s); //will select which coalition to join from the ones that offered
            s.addPartyToCoalition(selected,*this); //joining the selected coalition - will add to matrix and clone the agent
            mState = Joined;
        }
    }
}

int Party::getPartyId()
{
    return mId;
}

const vector<int>& Party::getOffersVector () const
{
    return didOffer;
}

void Party::initializeOffersVector(int n)
{
    for(int i=0; i<n; i++)
        didOffer.push_back(-1);

}

bool Party::hasOffer(int cId) const
{
    return didOffer[cId] != -1;
}

void Party::collectOffer(int cId)
{
    if(mState == Waiting)
    {
        mState = CollectingOffers; //if its the first offer will change the party state
    }
    offersTimer++;
    didOffer[cId] = offersTimer; //each offer has it's unique time
}

