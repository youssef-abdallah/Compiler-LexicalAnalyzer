#ifndef DFASTATE_H
#define DFASTATE_H
#include "includes.h"
#include "NFAState.h"

class DFAState
{
    private:
        bool acceptState;
        int stateId;
        string acceptStateToken;
        vector<NFAState> states;
        //set<int> statesId;

    public:
        DFAState();
        virtual ~DFAState();
        void setAcceptState(bool acceptState){
            this -> acceptState = acceptState;
        }
        bool isAcceptState(){
            return this->acceptState;
        }
        void setStateId(int id){
            this->stateId =id;
        }
        int getStateId(){
            return this->stateId;
        }
        void setAcceptStateToken(string acceptToken){
            this->acceptStateToken = acceptToken;
        }
        string getAcceptStateToken(){
            return this -> acceptStateToken;
        }
        /*void addState(NFAState state){
            if(statesId.count(state.getStateId())==0){
                states.push_back(state);
                statesId.insert(state.getStateId());
            }
        }*/

};

#endif // DFASTATE_H
