#include "includes.h"
#include "include/NFAState.h"
#include "include/LexicalAnalyzer.h"
#include "include/RegularExpression.h"
#include "include/NFABuilder.h"
#include "include/Scanner.h"
#include "include/Minimize.h"
#include "include/DFAState.h"

int main()
{
    LexicalAnalyzer::getInstance().execute();
    /*string x = "(0|(1.(0.1*.(0.0)*.0)*.1)*)*";
    NFAState s1, s2, s3;
    cout << s1.getStateId() << " " << s2.getStateId() << " " << s3.getStateId() << endl;
    RegularExpression regularExpression(x);
    //StateMachine nfa = NFABuilder::getInstance().buildNFAFromPostfix(regularExpression.getPostfixExpression());
    Scanner::getInstance().read_lexical_rules("test/lexical_rules.txt");
    vector<RegularDefinition> v = Scanner::getInstance().reg_definitions;
    RegularDefinition rd = v[2];
    vector<char> vc = rd.getValues();
    //cout << rd.values_to_string();

    vector<RegularExpression> vre = Scanner::getInstance().reg_expressions;
    cout << vre[2].getExpression() << endl << endl << vre[3].getExpression() << endl << endl << vre[4].getExpression() << endl << endl << vre[5].getExpression() << endl;*/


    /*DFAState A;
    A.setAcceptState(true);A.setStateId(1);A.setAcceptStateToken("id");
    DFAState B;
    B.setAcceptState(false);B.setStateId(2);
    DFAState C;
    C.setAcceptState(false);C.setStateId(3);
    DFAState D;
    D.setAcceptState(true);D.setStateId(4);D.setAcceptStateToken("digit");
    DFAState E;
    E.setAcceptState(true);E.setStateId(5);E.setAcceptStateToken("id");
    DFAState F;
    F.setAcceptState(false);F.setStateId(6);
    DFAState G;
    G.setAcceptState(true);G.setStateId(7);G.setAcceptStateToken("digit");

    vector<DFAState> states{A, B, C, D, E, F, G};
    vector<char> Inputs{'0', '1'};
    unordered_map<int, vector<int>> transitions;
    transitions[1] = {2, 6};
    transitions[2] = {1, 4};
    transitions[3] = {0, 7};
    transitions[4] = {2, 5};
    transitions[5] = {6, 6};
    transitions[6] = {1, 5};
    transitions[7] = {2, 5};
    Minimize min(states, Inputs, transitions);
    */


    return 0;
}
