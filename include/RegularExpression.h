#pragma once
#include "includes.h"

class RegularExpression {

public:
    RegularExpression();
    RegularExpression(string);
    ~RegularExpression();

    void setPostfixExpression(string postfixExpression) {
        this->postfixExpression = postfixExpression;
    }

    string getPostfixExpression() {
        if (postfixExpression == "") convertInfixToPostfix();
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
    int getPrecedence(char);
    bool isOperator(char);
    void convertInfixToPostfix();
};
