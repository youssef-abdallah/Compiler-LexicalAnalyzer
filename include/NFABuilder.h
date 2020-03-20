#pragma once
#include "includes.h"


class NFABuilder {

public:
    static NFABuilder& getInstance();

    NFABuilder(NFABuilder const&) = delete;
    void operator=(NFABuilder const&) = delete;

private:
    NFABuilder();
};
