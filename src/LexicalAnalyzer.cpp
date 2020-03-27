#include "../include/LexicalAnalyzer.h"
#include "Minimize.h"
#include "MinimizeDFASimulation.h"

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
                                                                 regularExpression.getExpressionType()));
    }
    NFAState initialState(0), finalState(0);
    for (StateMachine &stateMachine: stateMachines) {
        initialState.addTransition(0, stateMachine.getInitialState());
    }
    StateMachine &combinedStateMachine = *new StateMachine(initialState, finalState);
    DFABuilder builder(combinedStateMachine);
    builder.buildDFA();
    Minimize minimize(builder.getInitialState(),builder.GetAllState(),builder.GetInputs(),builder.getReducedTable());
    NFASimulator simulator;
    cout << simulator.simulate(combinedStateMachine, "123") << '\n';
    DFASimulator dfaSimulator;
    cout << dfaSimulator.simulate(builder.getInitialState(), "123") << '\n';
    MinimizeDFASimulation minsimulator(minimize);
    cout << minsimulator.GEtTokenForInput("123") << '\n';
    minsimulator.Reset();
    cout << minsimulator.GEtTokenForInput("F5nj7") << '\n';
    minsimulator.Reset();
    cout << minsimulator.GEtTokenForInput("\=\=") << '\n';
    minsimulator.Reset();
    cout << minsimulator.GEtTokenForInput("\+") << '\n';
    minsimulator.Reset();
    cout << minsimulator.GEtTokenForInput("\*") << '\n';
    minsimulator.Reset();
    cout << minsimulator.GEtTokenForInput("$") << '\n';
    minsimulator.Reset();
    cout << minsimulator.GEtTokenForInput("=") << '\n';
}
