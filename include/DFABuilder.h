#ifndef DFABUILDER_H
#define DFABUILDER_H
#include "NFAState.h"
#include "StateMachine.h"
#include "includes.h"
#include "DFAState.h"


class DFABuilder
{
    public:
        DFABuilder(StateMachine &machine): machineNFA(machine) {

        }
        virtual ~DFABuilder();
        void calculateEpsilonClosure();


    private:
        vector<reference_wrapper<DFAState>> allStates;
        map<set<int>, map<char,set<int>>> transitions;
        map<set<int>, DFAState> statesMap;
        stack<reference_wrapper<DFAState>> st;
        void calculateEpsilonClosure(NFAState &state);
        void getInitialState();
        void computeNewTable();
        bool checkIfNewState(set<int>);
        void checkIfAcceptState(DFAState &state);

        StateMachine &machineNFA;
        DFAState initialState;

        vector<char> inputs;
};

#endif // DFABUILDER_H
