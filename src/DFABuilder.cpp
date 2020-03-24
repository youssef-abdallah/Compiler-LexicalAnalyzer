#include "DFABuilder.h"


DFABuilder::~DFABuilder()
{
    //dtor
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
    state.getEpsilonClosure().push_back(state);
    unordered_map<int, bool> added;
    added[state.getStateId()] = 1;
    while (!st.empty())
    {
        NFAState &currentState = st.top();
        st.pop();
        for (NFAState &s : currentState.getEpsilonTransitions())
        {
            if (added[s.getStateId()] == 0)
            {
                st.push(s);
                state.getEpsilonClosure().push_back(s);
                added[s.getStateId()] = 1;
            }
        }
    }

    //state.setEpsilonClosure(stateClosure);
}

void DFABuilder::getInitialState(){
    NFAState &state = machineNFA.getInitialState();
    initialState = *new DFAState(0);
    set<int> initialId;
    for(NFAState &s : state.getEpsilonClosure()){
        initialState.addState(s);
        initialId.insert(s.getStateId());
    }
    allStates.push_back(initialState);
    statesMap.insert({initialState.getStatesId() , initialState});
    st.push(initialState);
}

void DFABuilder::computeNewTable(){
    while(!st.empty()){
        DFAState& s = st.top();
        st.pop();
        for(NFAState &currentNFAState : s.getNFAStates()){
            for ( auto &it : currentNFAState.getTransitions() ){
                for(NFAState &state : it.second){

                }
            }
        }
    }
}
