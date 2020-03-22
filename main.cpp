#include "includes.h"
#include "include/NFAState.h"
#include "include/LexicalAnalyzer.h"
#include "include/RegularExpression.h"
#include "include/NFABuilder.h"
#include "include/Scanner.h"

int main()
{
    string x = "(0|(1.(0.1*.(0.0)*.0)*.1)*)*";
    x = "0*";
    RegularExpression regularExpression(x);
    StateMachine nfa = NFABuilder::getInstance().buildNFAFromPostfix(regularExpression.getPostfixExpression());
    Scanner::getInstance().read_lexical_rules("test/lexical_rules.txt");
    vector<string> k = Scanner::getInstance().keywords;
    cout << k[0];
    return 0;
}
