#include "includes.h"

struct NFAState {

public:
    NFAState();
    NFAState(bool acceptState) {
        this->acceptState = acceptState;
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
private:
    bool acceptState;
    unordered_map<char, vector<NFAState>> transitions;
    vector<NFAState> epsilonTransitions;
};
