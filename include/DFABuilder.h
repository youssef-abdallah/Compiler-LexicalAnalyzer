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
        vector<reference_wrapper<DFAState>> buildDFA();
        vector<vector<int>> getReducedTable() {
            return this->reducedTable;
        }
        void buildReducedTable();


    private:
        vector<reference_wrapper<DFAState>> allStates;
        map<set<int>, map<char,set<int>>> transitions;
        map<set<int>, int> statesMap;
        stack<reference_wrapper<DFAState>> st;
        void calculateEpsilonClosure();
        void calculateEpsilonClosure(NFAState &state);
        void getInitialState();
        void computeNewTable();
        bool checkIfNewState(set<int>);
        void checkIfAcceptState(DFAState &state);
        vector<vector<int>> reducedTable;

        StateMachine &machineNFA;
        DFAState initialState;
        set<char> inputsSet;

};

#endif // DFABUILDER_H
