#include "RegularDefinition.h"

RegularDefinition::RegularDefinition() {


}

RegularDefinition::~RegularDefinition() {


}

void RegularDefinition::setValues(vector<char> v) {
	values = v;
}

vector<char> RegularDefinition::getValues() {
	return values;
}

void RegularDefinition::setDefinitionType(string type) {
	definition_type = type;
}

string RegularDefinition::getDefinitionType() {
	return definition_type;
}

string RegularDefinition::values_to_string() {
	string result = "";
	for (int i = 0; i < (int) values.size(); i++) {
		char next_value = values[i];
		result = result + next_value ;
		if (i != (int) values.size() - 1) {
			result = result + '|';
		}
	}
	return '(' + result + ')';
}
