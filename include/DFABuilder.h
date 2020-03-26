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

    private:
        set<DFAState> marked;
        void calculateEpsilonClosure();
        void calculateEpsilonClosure(NFAState &state);
        void initialize();
        void computeNewTable();
        void checkIfAcceptState(DFAState &state);
        StateMachine &machineNFA;
        DFAState initialState;
        set<char> inputsSet;
        DFAState& mov(DFAState &T, char symbol);

};

#endif // DFABUILDER_H
