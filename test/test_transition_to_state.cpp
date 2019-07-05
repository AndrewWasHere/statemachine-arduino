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

    Result result = machine.transition_to_state(&child1);

    assert(result == OK);
    assert((0 == std::strcmp("child 1", machine.active_state_name())));

    assert(result == OK);
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

    Result result = machine1.transition_to_state(&machine2);

    assert(result == STATE_TRANSITION_FAILED);

    result = machine1.transition_to_state(&child1);

    assert(result == OK);

    result = machine1.transition_to_state(&child2);

    assert(result == STATE_TRANSITION_FAILED);
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
    Result result = machine.transition_to_state(&child1);

    assert(result == OK);
    assert((0 == strcmp("child 1", machine.active_state_name())));
}

/*
 * Test transition to state with sub-state that has been previously entered.
 * Verify that m_active_state is not followed by `transition_to_state()`.
 */
void test_transition_to_state_with_history()
{
    std::cout << "test_transition_to_state_with_history()..." << std::endl;

    State machine("machine", nullptr);
    State child1("child 1", &machine);
    State child2("child 2", &child1);

    Result result = machine.transition_to_state(&child2);

    assert(result == OK);

    machine.transition_to_state(&child1);

    assert(result == OK);
    assert((0 == strcmp("child 1", machine.active_state_name())));
}

class SameStateTestState : public State
{
public:
    SameStateTestState(char const * name, State * parent) :
        State(name, parent),
        on_entry_calls(0),
        on_exit_calls(0)
    {}

    Result on_entry() override
    {
        ++on_entry_calls;
        return OK;
    }

    Result on_exit() override
    {
        ++on_exit_calls;
        return OK;
    }

    size_t on_entry_calls;
    size_t on_exit_calls;
};

void test_transition_to_same_state()
{
    std::cout << "test_transition_to_same_state()..." << std::endl;

    SameStateTestState machine("machine", nullptr);
    SameStateTestState child("child", &machine);

    Result result = machine.transition_to_state(&child);

    assert(result == OK);
    assert(child.on_entry_calls == 1);
    assert(child.on_exit_calls == 0);
    assert((0 == strcmp("child", machine.active_state_name())));

    result = machine.transition_to_state(&child);

    assert(result == OK);
    assert(child.on_entry_calls == 2);
    assert(child.on_exit_calls == 1);
    assert((0 == strcmp("child", machine.active_state_name())));
}