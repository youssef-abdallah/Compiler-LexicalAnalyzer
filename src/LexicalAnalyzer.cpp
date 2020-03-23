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
        stateMachines.push_back(NFABuilder::buildNFAFromPostfix(regularExpression.getPostfixExpression()));
    }
}
