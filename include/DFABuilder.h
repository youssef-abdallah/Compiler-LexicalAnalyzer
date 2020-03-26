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
        void buildDFA();
        DFAState& getInitialState() {
            return initialState;
        }

        unordered_map<int, vector<int>> getReducedTable() {
            return this->reducedTable;
        }

    private:
        map<set<int>, vector<reference_wrapper<DFAState>>> stateMapping;
        set<set<int>> marked;
        void calculateEpsilonClosure();
        void calculateEpsilonClosure(NFAState &state);
        void initialize();
        void computeNewTable();
        void checkIfAcceptState(DFAState &state);
        StateMachine &machineNFA;
        DFAState initialState;
        set<char> inputsSet;
        DFAState& mov(DFAState &T, char symbol);
        unordered_map<int, vector<int>> reducedTable;

};

#endif // DFABUILDER_H
