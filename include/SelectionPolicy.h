#pragma once

#include <vector>

class Graph;
class Agent;

class SelectionPolicy 
{ 
    public:
        virtual int select(const Graph& graph, const Agent& agent)=0;
        virtual SelectionPolicy* clone() = 0; //when implimented returns a new Selection Policy of the relevat type
        virtual ~SelectionPolicy() = default;
};

class MandatesSelectionPolicy: public SelectionPolicy
{ 
    public:
        virtual int select(const Graph& graph, const Agent& agent);
        virtual SelectionPolicy* clone();
};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{ 
    public:
        virtual int select(const Graph& graph, const Agent& agent);
        virtual SelectionPolicy* clone();
};