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
        void addState(NFAState &state) {
            if (!statesId.count(state.getStateId())) {
                statesId.insert(state.getStateId());
                states.push_back(state);
            }
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

        int getStateIndex() const {
            return stateIndex;
        }

        unordered_map<char, vector<reference_wrapper<DFAState>>> &getTransitions() {
            return this->transitions;
        }

        void addTransition(char symbol, DFAState &state) {
            this->getTransitions()[symbol].push_back(state);
        }

        bool operator < (DFAState const &obj) const {
            return this->stateIndex < obj.getStateIndex();
        }

    private:
        bool acceptState;
        //int stateId;
        string acceptStateToken;
        vector<reference_wrapper<NFAState>> states;
        unordered_map<char, vector<reference_wrapper<DFAState>>> transitions;
        set<int> statesId;
        int stateIndex;

};

#endif // DFASTATE_H
