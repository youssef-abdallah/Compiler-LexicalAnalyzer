#ifndef DFABUILDER_H
#define DFABUILDER_H
#include "NFAState.h"
#include "StateMachine.h"
#include "includes.h"


class DFABuilder
{
    public:
        DFABuilder(StateMachine &machine): machineNFA(machine) {

        }
        virtual ~DFABuilder();
        void calculateEpsilonClosure();

    private:
        /*vector<NFAState>*/
        void calculateEpsilonClosure(NFAState &state);
        StateMachine &machineNFA;
};

#endif // DFABUILDER_H
