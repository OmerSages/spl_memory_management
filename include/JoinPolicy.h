#pragma once

class Party;
class Simulation;

class JoinPolicy 
{
    public:
        virtual int join(const Party& party, const Simulation& sim)=0;
        virtual JoinPolicy* clone() = 0;  //when implimented returns a new Join Policy of the relevat type
        virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy 
{
    public:
        virtual int join(const Party& party, const Simulation& sim);
        virtual JoinPolicy* clone();
};

class LastOfferJoinPolicy : public JoinPolicy 
{
    public:
        virtual int join(const Party& party, const Simulation& sim);
        virtual JoinPolicy* clone();
};