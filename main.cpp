#include "includes.h"
#include "include/NFAState.h"
#include "include/LexicalAnalyzer.h"

int main()
{
    NFAState state1(0), state2(0);
    state1.addTransition(0, state2);
    NFAState x = state1.getEpsilonTransitions()[0];
    return 0;
}
