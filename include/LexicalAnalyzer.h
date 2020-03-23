#pragma once
#include "includes.h"



class LexicalAnalyzer {

public:
    static LexicalAnalyzer& getInstance();
    static void execute();

    LexicalAnalyzer(LexicalAnalyzer const&) = delete;
    void operator=(LexicalAnalyzer const&) = delete;

private:
    LexicalAnalyzer();
};
