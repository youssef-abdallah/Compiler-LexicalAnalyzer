#include "DFABuilder.h"

DFABuilder::DFABuilder()
{
    //ctor
}

DFABuilder::~DFABuilder()
{
    //dtor
}

void DFABuilder::calculateEpsilonClosure(){
    StateMachine machine = DFABuilder::machineNFA;
    int calculated[2000] = { };
    NFAState state = machine.getInitialState();
    calculated[state.getStateId()]=1;
    stack<NFAState> st;
    st.push(state);
    while(!st.empty()){
        NFAState s =st.top();
        st.pop();
        for(int i=0;i<s.getEpsilonTransitions().size();i++){
            if(calculated[(s.getEpsilonTransitions()[i]).getStateId()]==0){
                st.push(s.getEpsilonTransitions()[i]);
                calculateEpsilonClosure(s.getEpsilonTransitions()[i]);
                cout << s.getEpsilonTransitions()[i].getEpsilonClosure().size()<<endl;
                calculated[s.getEpsilonTransitions()[i].getStateId()]=1;
            }
        }
        /*for ( auto it = s.getTransitions().begin(); it != s.getTransitions().end(); ++it ){
                vector<NFAState> transitions = it->second;
                for(int i=0; i< transitions.size();i++){
                    if(calculated[transitions[i].getStateId()]==0){
                        st.push(transitions[i]);
                        calculateEpsilonClosure(transitions[i]);
                        calculated[transitions[i].getStateId()]=1;
                }
            }
        }*/
    }

}

void DFABuilder::calculateEpsilonClosure(NFAState &state){
    //vector<NFAState> stateClosure;
    stack<NFAState> st;
    st.push(state);
    state.epsilonClosure.push_back(state);
    int added[2000]={ };
    added[state.getStateId()];
    while(!st.empty()){
        NFAState s = st.top();
        st.pop();
        for(int i=0;i<s.getEpsilonTransitions().size();i++){
            if(added[s.getEpsilonTransitions()[i].getStateId()]==0){
                st.push(s.getEpsilonTransitions()[i]);
                state.epsilonClosure.push_back(s.getEpsilonTransitions()[i]);
                added[s.getEpsilonTransitions()[i].getStateId()]=1;
            }
        }
    }
    //state.setEpsilonClosure(stateClosure);
    cout<< state.getEpsilonClosure().size()<<endl;

}
