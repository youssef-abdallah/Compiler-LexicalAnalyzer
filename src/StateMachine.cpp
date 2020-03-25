#include "../include/StateMachine.h"


StateMachine::~StateMachine()
{
    //dtor
}

void StateMachine::concatenate(StateMachine &fsm) {
    this->getFinalState().setAcceptState(0);
    this->getFinalState().addTransition(0, fsm.getInitialState());
    this->setFinalState(fsm.getFinalState());
}

void StateMachine::unifyTwoMachines(StateMachine &fsm) {
    NFAState& initialState = *new NFAState(0);
    initialState.addTransition(0, this->getInitialState());
    initialState.addTransition(0, fsm.getInitialState());
    NFAState& finalState = *new NFAState(1);
    this->getFinalState().setAcceptState(0);
    fsm.getFinalState().setAcceptState(0);
    this->getFinalState().addTransition(0, finalState);
    fsm.getFinalState().addTransition(0, finalState);
    this->setInitialState(initialState);
    this->setFinalState(finalState);
}

void StateMachine::getTheMachineClosure() {
    NFAState& _initialState = *new NFAState(0);
    NFAState& _finalState = *new NFAState(1);
    NFAState &oldInitial = this->getInitialState();
    NFAState &oldFinal = this->getFinalState();
    _initialState.addTransition(0, _finalState);
    _initialState.addTransition(0, oldInitial);
    oldFinal.setAcceptState(0);
    oldFinal.addTransition(0, oldInitial);
    oldFinal.addTransition(0, _finalState);
    this->setInitialState(_initialState);
    this->setFinalState(_finalState);
    cout << this->getInitialState().getEpsilonTransitions()[1].get().getStateId() << endl;
}
