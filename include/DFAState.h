#ifndef DFASTATE_H
#define DFASTATE_H
#include "includes.h"


class DFAState
{
    public:
        DFAState();
        virtual ~DFAState();


    private:
        bool acceptState;
        int stateId;
        string acceptStateToken;
        //unordered_map<NFAState, vector<NFAState>> epsilonClosure;

};

#endif // DFASTATE_H
