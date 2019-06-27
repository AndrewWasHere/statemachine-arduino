/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include <iostream>
#include "test_construction.h"
#include "test_transition_to_state.h"
#include "test_transition_to_history.h"
#include "test_transition_to_deep_history.h"
#include "test_handle_event.h"

int main()
{
    std::cout << "Starting statemachine tests..." << std::endl;
    // Constructor tests.
    test_state_construction();

    // transition_to_state() tests.
    test_transition_to_good_state();
    test_transition_to_bad_state();
    test_transition_to_state_with_unused_history();
    test_transition_to_state_with_history();

    // transition_to_history() tests.
    test_history();

    // transition_to_deep_history() tests.
    test_deep_history();

    // handle_event() tests.
    test_handled_event();
    test_unhandled_event();

    std::cout << "Tests complete." << std::endl;
    
    return 0;
}