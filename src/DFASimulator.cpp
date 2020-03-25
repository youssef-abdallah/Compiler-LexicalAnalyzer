#include "DFASimulator.h"

DFASimulator::DFASimulator()
{
    //ctor
}

DFASimulator::~DFASimulator()
{
    //dtor
}

string DFASimulator::simulate(vector<reference_wrapper<DFAState>> states, vector<vector<int>> table, string inputString) {
    int currentState = 0;
    for (char& symbol : inputString) {
        currentState = table[currentState][symbol];
    }
    if (states[currentState].get().isAcceptState()) {
        return "ACCEPT";
    }
    return "REJECT";
}
