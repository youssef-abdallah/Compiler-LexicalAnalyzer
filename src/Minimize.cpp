#include<Minimize.h>

Minimize::Minimize(vector<DFAState> States, vector<char> Inputs, unordered_map<int, vector<int>> Transitions)
{
	this->States = States;
	this->Inputs = Inputs;
	this->Transitions = Transitions;
	this->Stop = false;
	Separate();

	while (!Stop) {
		Stop = true;
		Difference();
		UpdateColor();
	}

    RemoveDeadState();

	for (int i = 0; i < Nodes.size(); i++){
        cout << ((Node)Nodes[i]).GetStateName() << " " << ((Node)Nodes[i]).GetColor() << '\n';
	}
	/*vector<int> ele = (TransitionsMinimize.find(1))->second;
	cout << 'X' << " ->";
	for (int i = 0; i < ele.size(); i++){
        cout << " " << ele[i];
	}
	cout << '\n';
    ele = (TransitionsMinimize.find(2))->second;
	cout << 'Y' << " ->";
	for (int i = 0; i < ele.size(); i++){
        cout << " " << ele[i];
	}
	cout << '\n';
	ele = (TransitionsMinimize.find(3))->second;
	cout << 'Z' << " ->";
	for (int i = 0; i < ele.size(); i++){
        cout << " " << ele[i];
	}
	cout << '\n';
	ele = (TransitionsMinimize.find(4))->second;
	cout << 'U' << " ->";
	for (int i = 0; i < ele.size(); i++){
        cout << " " << ele[i];
	}
	cout << '\n';
	ele = (TransitionsMinimize.find(6))->second;
	cout << 'W' << " ->";
	for (int i = 0; i < ele.size(); i++){
        cout << " " << ele[i];
	}
	cout << '\n';
	ele = (TransitionsMinimize.find(7))->second;
	cout << 'M' << " ->";
	for (int i = 0; i < ele.size(); i++){
        cout << " " << ele[i];
	}
	cout << '\n';*/
}


void Minimize::Separate()
{
    int Color = 1;
    unordered_map<string, int> SetColor;
    for (int i = 0; i < States.size(); i++){
        DFAState Temp = States[i];
        if (Temp.isAcceptState()){
            auto check = SetColor.find(Temp.getAcceptStateToken());
            if(check == SetColor.end()){
                SetColor.emplace(Temp.getAcceptStateToken(), Color);
                Nodes.push_back(Node(States[i].getStateId(), Color));
                StateColor.emplace(States[i].getStateId(), Color);
                Color++;
            } else {
                Nodes.push_back(Node(States[i].getStateId(), check->second));
                StateColor.emplace(States[i].getStateId(), check->second);
            }
        } else {
            Nodes.push_back(Node(States[i].getStateId(), 0));
			StateColor.emplace(States[i].getStateId(), 0);
        }
    }
    StateColor.emplace(0, 0);
	/*bool CheckSome = false;
	for (int i = 0; i < States.size(); i++) {
		for (int j = 0; j < AcceptStates.size(); j++) {
			if (States[i] == AcceptStates[j]) {
				CheckSome = true;
				break;
			}
		}
		if (!CheckSome) {
			Nodes.push_back(Node(States[i], 0));
			StateColor.emplace(States[i], 0);
		}
		CheckSome = false;
	}
	for (int i = 0; i < AcceptStates.size(); i++) {
		Nodes.push_back(Node(AcceptStates[i], 1));
		StateColor.emplace(AcceptStates[i], 1);
	}
	*/
}

void Minimize::Difference()
{
	for (int i = 0; i < Nodes.size(); i++) {
        vector<int> Temp = (Transitions.find(((Node)(Nodes[i])).GetStateName()))->second;
		for (int j = 0; j < Temp.size(); j++) {
			Nodes[i].AppendString((StateColor.find(Temp[j]))->second);
		}
	}
	StateColor.clear();
	StateColor.emplace(0, 0);
}

void Minimize::UpdateColor()
{
	bool Case_2 = true;
	int Color = 0, preColor;
	for (int i = 0; i < Nodes.size(); i++) {
		preColor = Nodes[i].GetColor();
		auto temp = ColorUpdate.find(Nodes[i].GetString());
		if (!(temp == ColorUpdate.end())) {
			if (Nodes[i].GetColor() == (temp->second).GetPreColor()) {
				Case_2 = false;
				if (Nodes[i].GetColor() != (temp->second).GetCurColor()) {
					Stop = false;
				}
				Nodes[i].SetColor((temp->second).GetCurColor());
				StateColor.emplace(Nodes[i].GetStateName(), (temp->second).GetCurColor());
			}
		}
		if (Case_2){
			if (Nodes[i].GetColor() != Color) {
				Stop = false;
			}
			Nodes[i].SetColor(Color);
			ColorUpdate.emplace(Nodes[i].GetString(), ColorNode(preColor, Color));
			StateColor.emplace(Nodes[i].GetStateName(), Color);
			Color++;
		}
		Case_2 = true;
	}
	Color = 0;
	ColorUpdate.clear();
	ClearDifferStrings();
}

void Minimize::ClearDifferStrings()
{
	for (int i = 0; i < Nodes.size(); i++) {
		Nodes[i].ClearString();
	}
}

void Minimize::RemoveDeadState()
{
    unordered_map<int, int> Res;
    unordered_map<int, int> ChangeState;
    for (int i = 0; i < Nodes.size(); i++){
        auto temp = Res.find(Nodes[i].GetColor());
        if (temp == Res.end()){
            Res.emplace(Nodes[i].GetColor(), Nodes[i].GetStateName());
        } else {
            ChangeState.emplace(Nodes[i].GetStateName(), temp->second);
        }
    }
    for (int i = 0; i < Nodes.size(); i++){
        vector<int> Temp = (Transitions.find(((Node)(Nodes[i])).GetStateName()))->second;
        for (int j = 0; j < Temp.size(); j++){
            auto temp = ChangeState.find(Temp[j]);
            if (!(temp == ChangeState.end())){
                ((Transitions.find(((Node)(Nodes[i])).GetStateName()))->second)[j] = temp->second;
            }
        }
    }
    for (int i = 0; i < Nodes.size(); i++){
        auto temp = ChangeState.find(Nodes[i].GetStateName());
        if (temp == ChangeState.end()){
            TransitionsMinimize.emplace(Nodes[i].GetStateName(), (Transitions.find(Nodes[i].GetStateName()))->second);
        }
    }
}

Minimize::~Minimize()
{
	//dtor
}
