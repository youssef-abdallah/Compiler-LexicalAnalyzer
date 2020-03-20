#pragma once
#include "includes.h"



class LexicalAnalyzer {

public:
    static LexicalAnalyzer& getInstance();

    LexicalAnalyzer(LexicalAnalyzer const&) = delete;
    void operator=(LexicalAnalyzer const&) = delete;

private:
    LexicalAnalyzer();
};
