#ifndef MINIMIZEDFASIMULATION_H_INCLUDED
#define MINIMIZEDFASIMULATION_H_INCLUDED

#include<Minimize.h>

class MinimizeDFASimulation
{
private:
    int CurrentStateID;
	int initialStateID;
	unordered_map<int, vector<int>> Transitions;
	unordered_map<int, string> Tokens;
	vector<char> Input;
public:
	MinimizeDFASimulation(Minimize minimize);
	void Reset();
	string GEtTokenForInput(string InputString);
	~MinimizeDFASimulation();

};

#endif // MINIMIZEDFASIMULATION_H_INCLUDED
