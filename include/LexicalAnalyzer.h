#pragma once
#include "includes.h"
#include "NFAState.h"
#include "LexicalAnalyzer.h"
#include "RegularExpression.h"
#include "NFABuilder.h"
#include "Scanner.h"
#include "DFABuilder.h"
#include "NFASimulator.h"



class LexicalAnalyzer {

public:
    static LexicalAnalyzer& getInstance();
    static void execute();

    LexicalAnalyzer(LexicalAnalyzer const&) = delete;
    void operator=(LexicalAnalyzer const&) = delete;

private:
    LexicalAnalyzer();
    static StateMachine combineStateMachines(vector<StateMachine> &stateMachines);
};
