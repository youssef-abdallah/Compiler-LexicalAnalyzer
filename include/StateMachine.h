#pragma once
#include "includes.h"
#include "NFAState.h"



class StateMachine
{
    public:
        StateMachine();
        StateMachine(NFAState initialState, NFAState finalState) {
            this->initialState = initialState;
            this->finalState = finalState;
        }
        virtual ~StateMachine();
        NFAState getInitialState() {
            return this->initialState;
        }
        NFAState getFinalState() {
            return this->finalState;
        }
        void setInitialState(NFAState &state) {
            this->initialState = state;
        }
        void setFinalState(NFAState &state) {
            this->finalState = state;
        }
    private:
        NFAState initialState;
        NFAState finalState;
};

