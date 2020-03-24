#ifndef LIST_H_
#define LIST_H_
#include "includes.h"

struct NFAState {

public:
    NFAState() {
        this->acceptState = 0;
        this->stateId = stateCounter++;
    }
    NFAState(bool acceptState) {
        this->acceptState = acceptState;
        this->stateId = stateCounter++;
    }
    ~NFAState();
    void setAcceptState(bool acceptState) {
        this->acceptState = acceptState;
    }

    bool isAcceptState() {
        return this->acceptState;
    }

    void addTransition(char symbol, NFAState state) {
        if (symbol == 0) {
            epsilonTransitions.push_back(state);
        } else {
            transitions[symbol].push_back(state);
        }
    }

    vector<NFAState> getEpsilonTransitions() {
        return this->epsilonTransitions;
    }

    unordered_map<char, vector<NFAState>> getTransitions() {
        return this->transitions;
    }

    static int getStateCounter() {
        return NFAState::stateCounter;
    }

    int getStateId() {
        return this->stateId;
    }

    void setAcceptStateToken(string token) {
        this->acceptStateToken = token;
    }
    void setEpsilonClosure(vector<NFAState> eClosure){
        this->epsilonClosure = eClosure;
    }
    vector<NFAState> & getEpsilonClosure(){
        return this->epsilonClosure;
    }
    vector<NFAState> epsilonClosure;
private:
    static int stateCounter;
    int stateId;
    bool acceptState;
    unordered_map<char, vector<NFAState>> transitions;
    vector<NFAState> epsilonTransitions;
    string acceptStateToken;

};
// List.h code

#endif
