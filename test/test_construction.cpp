/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include <cassert>
#include <cstring>
#include <iostream>
#include "statemachine.h"

using namespace statemachine;

void test_state_construction()
{
    std::cout << "test_state_construction()..." << std::endl;

    char const * const name = "state-name";
    State s(name, nullptr);

    assert((0 == std::strcmp(name, s.active_state_name())));
}