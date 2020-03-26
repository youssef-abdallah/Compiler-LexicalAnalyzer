#include "DFASimulator.h"

DFASimulator::DFASimulator()
{
    //ctor
}

DFASimulator::~DFASimulator()
{
    //dtor
}

string DFASimulator::simulate(DFAState& state, string inputString) {
    for (char &symbol : inputString) {
        if (state.getTransitions()[symbol].size()) {
              state = state.getTransitions()[symbol][0];
        } else {
            return "REJECT";
        }
    }
    if (state.isAcceptState()) {
        return state.getAcceptStateToken();
    }
    return "REJECT";
}
