#include "../include/Scanner.h"


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
            cout << next_line << endl;
            if (next_line[0] == '{'){
                space_splitter(next_line, '{');
            } else if (next_line[0] == '['){
                space_splitter(next_line, '[');
            } else if (next_line.find(":") != string::npos){
                next_line = remove_spaces(next_line);
                regular_exp_scanner(next_line);
            } else if (next_line.find("=") != string::npos){
                next_line = remove_spaces(next_line);
                regular_def_scanner(next_line);
            }

        }
    }

    input_file.close();

}


void Scanner::space_splitter(string str, char delim)
{
    string line = str;
    line = line.substr(1, line.size() - 2);
    int index, pos;
    pos = 0;
    while ((index = line.find("\\", pos)) != (int) string::npos) {
        line.replace(index, 1, "" );
        pos = index + 1;
    }
    std::istringstream ss;
    ss.str(line);
    std::string token;
    // we need to check for leading spaces in the output keywords
    if (delim == '{') {
        while (std::getline(ss, token, ' ')) {
            keywords.push_back(token);
        }
    }
    else if (delim == '['){
        while (std::getline(ss, token, ' ')) {
            punctuations.push_back(token);
        }
    }
}

void Scanner::regular_def_scanner(string line){
    RegularDefinition rd;
    int split_pos = line.find('=');
    string definition_type = line.substr(0, split_pos);
    string RHS = line.substr(split_pos + 1, line.size() - split_pos);
    string def_string = "";

    vector<int> or_positions = find_all_occurences(RHS, '|');
    int st = 0;
    int endi = RHS.size();
    vector<char> values;

    if (or_positions.empty()) {
        vector<char> v = add_values(RHS, st, endi);
        if (v.empty()){
            for (int i = 0; i < (int) reg_definitions.size(); i++) {
                RegularDefinition temp_rd = reg_definitions[i];
                string defType = temp_rd.getDefinitionType();
                string replacement = temp_rd.values_to_string();
                if (defType + "+" == RHS.substr(st, defType.size() + 1)){
                    string temp_s = rd.values_to_string();
                    rd.set_values_string(temp_s + "|" + replacement + "~" + replacement + "*");
                } else if(defType == RHS.substr(st, defType.size())){
                    string temp_s = rd.values_to_string();
                    rd.set_values_string(temp_s + "|" + replacement);
                }
            }
        }
        else {
                rd.add_part_of_values(v);
        }
    }

    for (int j = 0; j < (int) or_positions.size(); j++) {
        endi = or_positions[j];
        vector<char> v ;
        v = add_values(RHS, st, endi);
        if (v.empty()){
            for (int i = 0; i < (int) reg_definitions.size(); i++) {
                RegularDefinition temp_rd = reg_definitions[i];
                string defType = temp_rd.getDefinitionType();
                string replacement = temp_rd.values_to_string();
                if (defType + "+" == RHS.substr(st, defType.size() + 1)){
                    string temp_s = rd.values_to_string();
                    rd.set_values_string(temp_s + "|" + replacement + "~" + replacement + "*");
                } else if(defType == RHS.substr(st, defType.size())){
                    string temp_s = rd.values_to_string();
                    rd.set_values_string(temp_s + "|" + replacement);
                }
            }
        }
        else{
            rd.add_part_of_values(v);
        }

        for (int i = 0; i < (int) v.size(); i++) {
            values.push_back(v[i]);
        }
        st = endi + 1;
        if (j == (int) or_positions.size() - 1){
            v = add_values(RHS, st, RHS.size());
            if (v.empty()){
            for (int i = 0; i < (int) reg_definitions.size(); i++) {
                RegularDefinition temp_rd = reg_definitions[i];
                string defType = temp_rd.getDefinitionType();
                string replacement = temp_rd.values_to_string();
                if (defType + "+" == RHS.substr(st, defType.size() + 1)){
                    string temp_s = rd.values_to_string();
                    rd.set_values_string(temp_s + "|" + replacement + "~" + replacement + "*");
                } else if(defType == RHS.substr(st, defType.size())){
                    string temp_s = rd.values_to_string();
                    rd.set_values_string(temp_s + "|" + replacement);
                }
            }
        }
        else{
            rd.add_part_of_values(v);
        }
            for (int i = 0; i < (int) v.size(); i++) {
                values.push_back(v[i]);
            }
        }
    }

    rd.setDefinitionType(definition_type);
    rd.setValues(values);
    reg_definitions.push_back(rd);

}


void Scanner::regular_exp_scanner(string line) {
    has_definitions = false;
    int split_pos = line.find(':');
    string expression_type = line.substr(0, split_pos);
    string RHS = line.substr(split_pos + 1, line.size() - split_pos);
    sort(reg_definitions.begin(), reg_definitions.end());
    for (int i = 0; i < (int) reg_definitions.size(); i++) {
        RegularDefinition rd = reg_definitions[i];
        string defType = rd.getDefinitionType();
        string replacement = rd.values_to_string();
        RHS = remove_plus_operator(RHS, defType);
        RHS = replace_definitions(RHS, defType, replacement);

    }

        RHS = handle_special_operators(RHS);
        RHS = additional_manipulations(RHS);


    RegularExpression re;
    re.setExpression(RHS);
    re.setExpressionType(expression_type);
    reg_expressions.push_back(re);

}

vector<int> Scanner::find_all_occurences(string line, char delim) {
    vector<int> results;
    for (int i = 0; i < (int) line.size(); i++) {
        if (line[i] == delim)
            results.push_back(i);
    }
    return results;
}


vector<char> Scanner::add_values(string str, int start, int endi) {
    vector<char> results;
    string line = str.substr(start, endi - start);
    if (line.find('-') == string::npos) {
        if (str.size() == 1) results.push_back(line[start]);
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
        while ((index = RHS.find(defType + "+", pos)) != (int) string::npos) {
            RHS.replace(index, defType.size() + 1, defType + defType + "*");
            pos = index + 1;
        }

        pos = 0;
        while ((index = RHS.find(")+", pos)) != (int) string::npos) {
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
    while ((index = RHS.find(defType, pos)) != (int) string::npos) {
        if (replacement.find(")|") != string::npos){
            has_definitions = true;
            RHS.replace(index, defType.size(), "(" + replacement + ")" + conc_operator);
        } else {
            has_definitions = true;
            RHS.replace(index, defType.size(), replacement + conc_operator);
        }

        pos = index + 1;
    }
    return RHS;
}

string Scanner::additional_manipulations(string line) {
    string RHS = line;
    int index;
    int pos = 0;

    while ((index = RHS.find("~*", pos)) != (int) string::npos) {
        RHS.replace(index, 2, "*");
        pos = index + 1;
    }
/*
    while ((index = RHS.find("~+", pos)) != (int) string::npos) {
        RHS.replace(index, 2, "*");
        pos = index + 1;
    }
*/
    pos = 0;
    while ((index = RHS.find("~)", pos)) != (int) string::npos) {
        RHS.replace(index, 2, ")");
        pos = index + 1;
    }

    pos = 0;
    while ((index = RHS.find("~|", pos)) != (int) string::npos) {
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
    while ((index = RHS.find("\\L", pos)) != (int) string::npos) {
        RHS.replace(index, 2, "" + epsilon);
        pos = index + 1;
    }

    pos = 0;
    while ((index = RHS.find("\\", pos)) != (int) string::npos) {
        RHS.replace(index, 1, "" );
        pos = index + 1;
    }

    if (!has_definitions){

        RHS = add_backslash_before(RHS, "*");
        RHS = add_backslash_before(RHS, "+");
        RHS = add_backslash_before(RHS, "~");
        pos = 0;
        while ((index = RHS.find("|", pos)) != (int) string::npos) {
            if (index - pos > 1){
                RHS = insert_concatination_op(RHS, pos, index - pos);
            }
            pos = index + 1;
        }
        if (pos != 0){
            RHS = insert_concatination_op(RHS, pos, RHS.size() - pos + 1);
        }

    }

    return RHS;
}

string Scanner::remove_spaces(string line){
    string str = line;
    int index;
    int pos = 0;
    while ((index = str.find(" ", pos)) != (int) string::npos) {
        str.replace(index, 1, "" );
        pos = index + 1;
    }
    return str;
}

string Scanner::insert_concatination_op(string line, int st, int length){
    string str = line;
    int pos = st;
    int i = length - 1;
    while (i > 0){
        string LHS = str.substr(0, pos - 0 + 1);
        if (LHS[LHS.size() - 1] == '\\') {
            i--;
            continue;
        }
        string RHS = str.substr(pos + 1, str.size() - pos);
        str = LHS + conc_operator + RHS;
        pos += 2;
        i--;
    }
    return str;
}

string Scanner::add_backslash_before(string line, string op){
    string str = line;
    int index;
    int pos = 0;
    while ((index = str.find(op, pos)) != (int) string::npos) {

        str.replace(index, 1, "\\" + op );
        pos = index + 2;
    }
    return str;
}
