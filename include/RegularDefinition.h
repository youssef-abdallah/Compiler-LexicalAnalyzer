#pragma once
#include "includes.h"

class RegularDefinition
{
public: 

	string values_to_string();
	void setValues(vector<char> v);
	void setDefinitionType(string type);
	vector<char> getValues();
	string getDefinitionType();

private: 

	string definition_type;
	vector<char> values;

};

