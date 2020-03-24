#include "../include/LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer() {

}

LexicalAnalyzer& LexicalAnalyzer::getInstance() {
    static LexicalAnalyzer instance;
    return instance;
}

void LexicalAnalyzer::execute() {
    Scanner::getInstance().read_lexical_rules("./test/lexical_rules.txt");
    vector<RegularExpression> regularExpressions = Scanner::getInstance().reg_expressions;
    vector<StateMachine> stateMachines;
    for (RegularExpression regularExpression : regularExpressions) {
        stateMachines.push_back(NFABuilder::buildNFAFromPostfix(regularExpression.getPostfixExpression(),
                                                                 regularExpression.getExpression()));
    }
    StateMachine combinedStateMachine = LexicalAnalyzer::combineStateMachines(stateMachines);
    DFABuilder builder(combinedStateMachine);
    builder.calculateEpsilonClosure();
}

StateMachine LexicalAnalyzer::combineStateMachines(vector<StateMachine> &stateMachines) {
    NFAState initialState(0);
    for (StateMachine &stateMachine: stateMachines) {
        initialState.addTransition(0, stateMachine.getInitialState());
    }
    // There are multiple final states in this machine, so set its final state to null.
    return StateMachine(initialState, 0);
}
