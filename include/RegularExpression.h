#include "includes.h"

class RegularExpression {

public:
    RegularExpression();
    ~RegularExpression();
private:
    std::string expression, postfixExpression;

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
};
