#include "DFABuilder.h"


DFABuilder::~DFABuilder()
{
    //dtor
}

void DFABuilder::calculateEpsilonClosure()
{
    int calculated[2000] = {0};
    NFAState &state = machineNFA.getInitialState();
    calculateEpsilonClosure(state);
    calculated[state.getStateId()] = 1;
    stack<NFAState> st;
    st.push(state);
    while (!st.empty())
    {
        NFAState s = st.top();
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

        for ( auto it : s.getTransitions() )
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
    stack<NFAState> st;
    st.push(state);
    state.getEpsilonClosure().push_back(state);
    int added[2000] = {0};
    added[state.getStateId()] = 1;
    while (!st.empty())
    {
        NFAState currentState = st.top();
        st.pop();
        for (NFAState & s: currentState.getEpsilonTransitions())
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
