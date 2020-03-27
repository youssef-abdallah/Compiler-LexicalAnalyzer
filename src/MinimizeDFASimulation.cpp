#include <MinimizeDFASimulation.h>

MinimizeDFASimulation::MinimizeDFASimulation(Minimize minimize){
    this->initialStateID = minimize.GetInitialID();
    this->Transitions = minimize.GetTransitions();
    this->Tokens = minimize.GetTokens();
    this->Input = minimize.GetInputVector();
    CurrentStateID = initialStateID;
}
void MinimizeDFASimulation::Reset(){
    CurrentStateID = initialStateID;
}

string MinimizeDFASimulation::GEtTokenForInput(string InputString){
    for (char Symbol : InputString) {
        auto it = std::find(Input.begin(), Input.end(), Symbol);
        int Pos = it - Input.begin();
        auto iter = Transitions.find(CurrentStateID);
        if (iter != Transitions.end()){
            vector<int> Temp = iter->second;
            CurrentStateID = Temp[Pos];
        }else {
            return "REJECT";
        }

    }
    auto t = Tokens.find(CurrentStateID);
    if (t != Tokens.end()){
        return t->second;
    } else{
        return "REJECT";
    }
}

MinimizeDFASimulation::~MinimizeDFASimulation(){
}
