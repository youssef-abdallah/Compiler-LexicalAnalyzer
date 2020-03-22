#include "..\include\Scanner.h"


Scanner::Scanner() {

}

Scanner& Scanner::getInstance() {
    static Scanner instance;
    return instance;
}

void Scanner::read_lexical_rules(std::string file_name){
    fstream input_file;
    input_file.open (file_name, std::fstream::in | std::fstream::out | std::fstream::app);
    string next_line;

    if (input_file.is_open()){
        while (getline(input_file, next_line)){
            if (next_line.find("{") != string::npos){
                space_splitter(next_line, '{');
            } else if (next_line.find("[") != string::npos){
                space_splitter(next_line, '[');
            } else if (next_line.find(":") != string::npos){
                regular_exp_scanner(next_line);
            } else if (next_line.find("=") != string::npos){
                regular_def_scanner(next_line);
            }
        }
    }

}


void Scanner::space_splitter(string str, char delim)
{
    string line = str;
    line = line.substr(1, line.size() - 2);
    std::istringstream ss;
    ss.str(line);
    std::string token;
    // we need to check for leading spaces in the output keywords
    if (delim == '{') {
        while (std::getline(ss, token, delim)) {
            keywords.push_back(token);
        }
    }
    else if (delim == '['){
        while (std::getline(ss, token, delim)) {
            punctuations.push_back(token);
        }
    }
}

void Scanner::regular_def_scanner(string line){
    int split_pos = line.find('=');
    string definition_type = line.substr(0, split_pos);
    string RHS = line.substr(split_pos + 1, line.size() - split_pos);
    vector<int> or_positions = find_all_occurences(RHS, '|');
    int st = 0;
    int end = RHS.size();
    vector<char> values;
    if (or_positions.empty()) {
        vector<char> v = add_values(RHS, st, end);
        for (int i = 0; i < v.size(); i++) {
            values.push_back(v[i]);
        }
    }
    for (int j = 0; j < or_positions.size(); j++) {
        end = or_positions[j];
        vector<char> v = add_values(RHS, st, end);
        for (int i = 0; i < v.size(); i++) {
            values.push_back(v[i]);
        }
        st = end + 1;
    }
    RegularDefinition rd;
    rd.setDefinitionType(definition_type);
    rd.setValues(values);
    reg_definitions.push_back(rd);

}


void Scanner::regular_exp_scanner(string line) {
    int split_pos = line.find(':');
    string expression_type = line.substr(0, split_pos);
    string RHS = line.substr(split_pos + 1, line.size() - split_pos);
    //RHS.erase(std::remove_if(RHS.begin(), RHS.end(), ::isspace), RHS.end());

    for (int i = 0; i < reg_definitions.size(); i++) {
        RegularDefinition rd = reg_definitions[i];
        string defType = rd.getDefinitionType();
        string replacement = rd.values_to_string();

        RHS = remove_plus_operator(RHS, defType);
        RHS = replace_definitions(RHS, defType, replacement);
        RHS = handle_special_operators(RHS);
        RHS = additional_manipulations(RHS);

    }


    RegularExpression re;
    re.setExpression(RHS);
    reg_expressions.push_back(re);


}

vector<int> Scanner::find_all_occurences(string line, char delim) {
    vector<int> results;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == delim)
            results.push_back(i);
    }
    return results;
}


vector<char> add_values(string str, int start, int end) {
    vector<char> results;
    string line = str.substr(start, end - start);
    //line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
    if (line.find('-') == string::npos) {
        results.push_back(line[start]);
    }
    else {
        int pos = line.find('-');
        char first = line[pos - 1];
        char last = line[pos + 1];
        int i = first;
        while (i <= last) {
            char c = i;
            results.push_back(c);
            i++;
        }
    }
    return results;
}


string Scanner::remove_plus_operator(string line, string defType) {

        string RHS = line;
        int index;
        int pos = 0;
        while ((index = RHS.find(defType + "+", pos)) != string::npos) {
            RHS.replace(index, defType.size() + 1, defType + defType + "*");
            pos = index + 1;
        }

        pos = 0;
        while ((index = RHS.find(")+", pos)) != string::npos) {
            int start_pos;
            for (int j = index; j >= 0; j--) {
                if (RHS[j] == '(') {
                    start_pos = j;
                    break;
                }
            }
            string parentheses = RHS.substr(start_pos, index - start_pos + 1);
            RHS.replace(start_pos, index - start_pos + 2, parentheses + conc_operator + parentheses + "*");
            pos = index + 1;
        }

        return RHS;

}


string Scanner::replace_definitions(string line, string defType, string replacement) {
    string RHS = line;
    int index;
    int pos = 0;
    while ((index = RHS.find(defType, pos)) != string::npos) {
        RHS.replace(index, defType.size(), replacement + conc_operator);
        pos = index + 1;
    }

}

string Scanner::additional_manipulations(string line) {
    string RHS = line;
    int index;
    int pos = 0;

    while ((index = RHS.find(conc_operator + "*", pos)) != string::npos) {
        RHS.replace(index, 2, "*");
        pos = index + 1;
    }

    pos = 0;
    while ((index = RHS.find(conc_operator + ")", pos)) != string::npos) {
        RHS.replace(index, 2, ")");
        pos = index + 1;
    }

    pos = 0;
    while ((index = RHS.find(conc_operator + "|", pos)) != string::npos) {
        RHS.replace(index, 2, "|");
        pos = index + 1;
    }

    if (RHS[RHS.size() - 1] == conc_operator) {
        RHS.replace(RHS.size() - 1, 1, "");
    }

    return RHS;
}

string Scanner::handle_special_operators(string line) {
    string RHS = line;
    int index;
    int pos = 0;
    while ((index = RHS.find("\\L", pos)) != string::npos) {
        RHS.replace(index, 2, "" + epsilon);
        pos = index + 1;
    }

    pos = 0;
    while ((index = RHS.find("\\", pos)) != string::npos) {
        RHS.replace(index, 1, "" );
        pos = index + 1;
    }

    return RHS;
}
