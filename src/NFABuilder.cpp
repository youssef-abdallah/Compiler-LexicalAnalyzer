#include "NFABuilder.h"

NFABuilder::NFABuilder() {

}

NFABuilder& NFABuilder::getInstance() {
    static NFABuilder instance;
    return instance;
}
