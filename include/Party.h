#pragma once
#include <string>
#include <vector>

using std::vector;
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


    bool hasOffer(int cId) const; //return true if the party recieved an offer for the coalition
    const vector<int>& getOffersVector() const;
    void collectOffer(int cId);
    void initializeOffersVector(int size);
    int getPartyId();

    //rule of 5
    virtual ~Party(); //destructor
    Party(const Party& other); //copy constractur
    Party(Party&& other); //move constructor
    Party& operator=(const Party& other); //copy assignemt operator
    Party& operator=(Party&& other); //move assignemt operator

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;


    int iterTimer;   
    int offersTimer;  //holds the time when each offer to the party has been made
    vector<int> didOffer; //coalitions joining offers
};
