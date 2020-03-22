#include "includes.h"

class RegularExpression {

public:
    RegularExpression();
    ~RegularExpression();

    void setPostfixExpression(string postfixExpression) {
        this->postfixExpression = postfixExpression;
    }

    string getPostfixExpression() {
        return postfixExpression;
    }

    void setExpression(string expression) {
        this->expression = expression;
    }

    string getExpression() {
        return expression;
    }
private:
    std::string expression, postfixExpression;

};
