#include "DFABuilder.h"


DFABuilder::~DFABuilder()
{
    //dtor
}

vector<reference_wrapper<DFAState>> DFABuilder::buildDFA(){
    calculateEpsilonClosure();
    getInitialState();
    computeNewTable();
    cout<<allStates.size()<<endl;
    return allStates;
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
            if(inputsSet.count(it.first)==0){
                inputsSet.insert(it.first);
                inputs.push_back(it.first);
            }
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

void DFABuilder::getInitialState(){
    NFAState &state = machineNFA.getInitialState();
    initialState = *new DFAState(0);
    set<int> initialId;
    for(NFAState &s : state.getEpsilonClosure()){
        initialState.addState(s);
        initialId.insert(s.getStateId());
    }
    //allStates.push_back(initialState);
    statesMap.insert({initialState.getStatesId() , initialState});
    st.push(initialState);
}

/*void DFABuilder::computeNewTable(){
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
}*/
void DFABuilder::computeNewTable(){
    for(int i=0;i<127;i++){
        inputs.push_back((char) i);
    }
    while(!st.empty()){
        DFAState& rowState = st.top();
        st.pop();
        map<char,set<int>> innerMap;
        for(char c : inputs){
           DFAState transitionState = *new DFAState(0);
            for(NFAState &currentState : rowState.getNFAStates()){
                for(NFAState &state : currentState.getTransitions()[c]){
                    for(NFAState &closureState : state.getEpsilonClosure()){
                            transitionState.addState(closureState);
                    }
                }
            }
            //put the new state in the transitions map
            innerMap.insert({c,transitionState.getStatesId()});
            transitions.insert({rowState.getStatesId(),innerMap});
            //check if this is a new state or not...
            //if yes push the statesId set into the stack to compute the new row
            if(checkIfNewState(transitionState.getStatesId())){
                st.push(transitionState);
                statesMap.insert({transitionState.getStatesId() , transitionState});
                //check if it contains any accept state and get accept state token
                checkIfAcceptState(transitionState);
            }
        }
        allStates.push_back(rowState);
    }
}

bool DFABuilder::checkIfNewState(set<int> newSet){
    if(transitions.count(newSet)==0){
        return 1;
    }
    return 0;
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
