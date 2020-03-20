#pragma once
#include "includes.h"


class Scanner {

public:
    static Scanner& getInstance();

    Scanner(Scanner const&) = delete;
    void operator=(Scanner const&) = delete;

private:
    Scanner();
};
