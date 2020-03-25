#ifndef DFASTATE_H
#define DFASTATE_H
#include "includes.h"
#include "NFAState.h"

class DFAState
{
    public:
        DFAState();
        DFAState(bool accept){
            this->acceptState=accept;
        }
        virtual ~DFAState();
        void setAcceptState(bool acceptState){
            this->acceptState=acceptState;
        }
        bool isAcceptState(){
            return this->acceptState;
        }
        void setAcceptStateToken(string token){
            this->acceptStateToken=token;
        }
        string getAcceptStateToken(){
            return this->acceptStateToken;
        }
        bool addState(NFAState &state){
            if(statesId.count(state.getStateId())==0){
                statesId.insert(state.getStateId());
                states.push_back(state);
                return 1;
            }
            return 0;
        }
        vector<reference_wrapper<NFAState>> getNFAStates(){
            return this->states;
        }
        set<int> getStatesId(){
            return this->statesId;
        }

        void setStateIndex(int index) {
            this->stateIndex = index;
        }

        int getStateIndex() {
            return stateIndex;
        }

    private:
        bool acceptState;
        //int stateId;
        string acceptStateToken;
        vector<reference_wrapper<NFAState>> states;
        set<int> statesId;
        int stateIndex;

};

#endif // DFASTATE_H
