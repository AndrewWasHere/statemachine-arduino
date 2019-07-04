/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See
    LICENSE.txt or https://opensource.org/licenses/BSD-3-Clause.
*/
#include <cassert>
#include <cstring>
#include "statemachine.h"

using namespace statemachine;

class InitializeTestState : public State
{
public:
    InitializeTestState(char const * name, State * parent) :
        State(name, parent),
        on_initialize_called(0)
    {}

    Result on_initialize() override;

    int on_initialize_called;
};

InitializeTestState machine("machine", nullptr);
State child("child", &machine);

Result InitializeTestState::on_initialize()
{
    ++on_initialize_called;
    transition_to_state(&child);
    return OK;
}

void test_initialize_machine()
{
    machine.transition_to_state(&machine);

    assert(0 == std::strcmp("child", machine.active_state_name()));
}