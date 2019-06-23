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
 * Test happy paths for `transition_to_state()`.
 * - machine to child state.
 * - state to state.
 */
void test_transition_to_good_state()
{
    std::cout << "test_transition_to_good_state()..." << std::endl;

    State machine("machine", nullptr);
    State child1("child 1", &machine);
    State child2("child 2", &machine);

    machine.transition_to_state(&child1);

    assert((0 == std::strcmp("child 1", machine.active_state_name())));

    machine.transition_to_state(&child2);

    assert((0 == std::strcmp("child 2", machine.active_state_name())));
}

/*
 * Test unhappy paths for `transition_to_state()`.
 * - machine to non-child state.
 * - state to non-machine state.
 */
void test_transition_to_bad_state()
{
    std::cout << "test_transition_to_bad_state()..." << std::endl;

    State machine1("machine 1", nullptr);
    State child1("child 1", &machine1);
    State machine2("machine 2", nullptr);
    State child2("child 2", &machine2);

    bool exception_thrown = false;
    try
    {
        machine1.transition_to_state(&machine2);
    }
    catch(BadStateException &)
    {
        exception_thrown = true;
    }

    assert(exception_thrown);

    machine1.transition_to_state(&child1);
    try
    {
        machine1.transition_to_state(&child2);
    }
    catch(BadStateException &)
    {
        exception_thrown = true;
    }

    assert(exception_thrown);
}

/*
 * Test transition to state with sub-state that has never been entered.
 */
void test_transition_to_state_with_unused_history()
{
    std::cout << "test_transition_to_state_with_unused_history()..." << std::endl;

    State machine("machine", nullptr);
    State child1("child 1", &machine);
    State child2("child 2", &child1);

    child2.active_state_name();  // This is here to quiet the linter about unused variables.
    machine.transition_to_state(&child1);

    assert((0 == strcmp("child 1", machine.active_state_name())));
}

/*
 * Test transition to state with sub-state that has been previously entered.
 * Verify that m_active_state is not followed by `transition_to_state()`.
 */
void test_transition_to_state_with_history()
{
    std::cout << "test_transition-to_state_with_history()..." << std::endl;

    State machine("machine", nullptr);
    State child1("child 1", &machine);
    State child2("child 2", &child1);

    machine.transition_to_state(&child2);
    machine.transition_to_state(&child1);

    assert((0 == strcmp("child 1", machine.active_state_name())));
}