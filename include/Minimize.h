#ifndef MINIMIZE_H_INCLUDED
#define MINIMIZE_H_INCLUDED

#include<includes.h>
#include<Node.h>
#include<ColorNode.h>
#include<algorithm>
#include<DFAState.h>

class Minimize
{
private:
	vector<DFAState> States;
	vector<char> Inputs;
	unordered_map<int, vector<int>> Transitions;
	unordered_map<int, vector<int>> TransitionsMinimize;
	unordered_map<string, ColorNode> ColorUpdate;
	unordered_map<int, int> StateColor;
	vector<Node> Nodes;
	bool Stop;
	void Separate();
	void Difference();
	void UpdateColor();
	void ClearDifferStrings();
	void RemoveDeadState();
public:
	Minimize(vector<DFAState> States, vector<char> Inputs, unordered_map<int, vector<int>> Transitions);
	~Minimize();
};

#endif // MINIMIZE_H_INCLUDED
