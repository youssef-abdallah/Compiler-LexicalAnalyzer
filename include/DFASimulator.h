#ifndef DFASIMULATOR_H
#define DFASIMULATOR_H
#include "includes.h"
#include "DFAState.h"


class DFASimulator
{
    public:
        DFASimulator();
        virtual ~DFASimulator();
        string simulate(vector<reference_wrapper<DFAState>>, vector<vector<int>>, string);

    protected:

    private:
};

#endif // DFASIMULATOR_H
