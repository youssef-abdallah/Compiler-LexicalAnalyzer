#include "DFABuilder.h"


DFABuilder::~DFABuilder()
{
    //dtor
}

void DFABuilder::buildDFA(){
    calculateEpsilonClosure();
    initialize();
    computeNewTable();
}

void DFABuilder::calculateEpsilonClosure()
{
    NFAState &state = machineNFA.getInitialState();
    calculateEpsilonClosure(state);
    unordered_map<int, bool> calculated;
    calculated[state.getStateId()] = 1;
    stack<reference_wrapper<NFAState>> st;
    st.push(state);
    while (!st.empty())
    {
        NFAState& s = st.top();
        st.pop();
        for (NFAState &currentState : s.getEpsilonTransitions())
        {
            if (!calculated[currentState.getStateId()])
            {
                st.push(currentState);
                calculateEpsilonClosure(currentState);
                calculated[currentState.getStateId()] = 1;
            }
        }

        for ( auto &it : s.getTransitions() )
        {
            inputsSet.insert(it.first);
            for(NFAState &currentState : it.second)
            {
                if (!calculated[currentState.getStateId()])
                {
                    st.push(currentState);
                    calculateEpsilonClosure(currentState);
                    calculated[currentState.getStateId()] = 1;
                }
            }
        }
    }
}

void DFABuilder::calculateEpsilonClosure(NFAState &state)
{
    //vector<NFAState> stateClosure;
    stack<reference_wrapper<NFAState>> st;
    st.push(state);
    unordered_set<int> added;
    while (!st.empty())
    {
        NFAState &currentState = st.top();
        st.pop();
        added.insert(currentState.getStateId());
        state.getEpsilonClosure().push_back(currentState);
        for (NFAState &nextState : currentState.getEpsilonTransitions())
        {
            //cout << added.count(nextState.getStateId()) << endl;
            if (!added.count(nextState.getStateId()))
            {
                st.push(nextState);
            }
        }
    }
}

void DFABuilder::initialize() {
    NFAState &state = machineNFA.getInitialState();
    initialState = *new DFAState(0);
    set<int> initialId;
    for(NFAState &s : state.getEpsilonClosure()){
        initialState.addState(s);
        initialId.insert(s.getStateId());
    }
}

void DFABuilder::computeNewTable() {
    vector<reference_wrapper<DFAState>> Dstates;
    Dstates.push_back(initialState);
    for (int i = 0; i < (int) Dstates.size(); i++) {
        DFAState &T = Dstates[i];
        if (marked.count(T)) continue;
        marked.insert(T);
        for (char a : inputsSet) {
            DFAState& U = mov(T, a);
            T.addTransition(a, U);
            if (marked.count(U) == 0) Dstates.push_back(U);
        }
    }
}


void DFABuilder::checkIfAcceptState(DFAState &state){
    int minId=99999;
    for(NFAState &s : state.getNFAStates()){
        if(s.isAcceptState()){
            if(s.getStateId()<minId){
                state.setAcceptState(1);
                state.setAcceptStateToken(s.getAcceptStateToken());
            }
        }
    }
}

DFAState& DFABuilder::mov(DFAState &T, char symbol) {
    DFAState& newState = *new DFAState(0);
    for (NFAState &nfaState : T.getNFAStates()) {
        vector<reference_wrapper<NFAState>> nextStates = nfaState.getTransitions()[symbol];
        for (NFAState &nextState : nextStates) {
            for (NFAState& epsilonState : nextState.getEpsilonClosure()) {
                newState.addState(epsilonState);
            }
        }
    }
    checkIfAcceptState(newState);
    return newState;
}
