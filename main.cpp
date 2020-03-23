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
    vector<RegularDefinition> v = Scanner::getInstance().reg_definitions;
    RegularDefinition rd = v[2];
    vector<char> vc = rd.getValues();
    //cout << rd.values_to_string();

    vector<RegularExpression> vre = Scanner::getInstance().reg_expressions;
    //cout << vre[0].getExpression() << endl << endl << vre[1].getExpression() << endl << endl << vre[2].getExpression() << endl;

return 0;

}

