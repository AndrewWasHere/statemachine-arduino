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

/*
 * Test transition to history.
 */
void test_history()
{
    std::cout << "test_history()..." << std::endl;

    State machine("machine", nullptr);
    State c1("c1", &machine);
    State c2("c2", &machine);
    State d1("d1", &c2);
    State d2("d2", &c2);
    State e1("e1", &d2);

    machine.transition_to_state(&c1);

    assert((0 == std::strcmp("c1", machine.active_state_name())));

    // History transition to a state with no history.
    machine.transition_to_history(&c2);

    assert((0 == std::strcmp("c2", machine.active_state_name())));

    // History transition to a state with history.
    machine.transition_to_state(&d1);
    machine.transition_to_history(&c2);

    assert((0 == std::strcmp("d1", machine.active_state_name())));

    machine.transition_to_state(&c1);
    machine.transition_to_history(&c2);

    assert((0 == std::strcmp("d1", machine.active_state_name())));

    // History transition to a state with deep history.
    machine.transition_to_state(&e1);
    machine.transition_to_history(&c2);

    assert((0 == std::strcmp("d2", machine.active_state_name())));
}