/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#pragma once

#include "event.h"

namespace statemachine
{
    /*
        Base class for states in the finite state machine.
     */
    class State
    {
    public:
        /*
            State machine state constructor.

            Pass nullptr as the parent state for the root state machine state.
            Otherwise, pass the parent state as the `parent` argument.
         */
        State(char const * const name, State * const parent);

        /*
            Transition to new state.
         */
        void transition_to_state(State * const state);

        /*
            Call this from the state machine root class instance to process
            an event.
         */
        void handle_event(Event & event);

        /*
            Return the name of the active state.
         */
        char const * const active_state_name();
        
    protected:
        /*
            Override this function to provide functionality for whenever your
            derived state is entered via a `transition_to_state` call.
         */
        void on_entry() {}

        /*
            Override this function to provide functionality for whenever your
            derived state is exited via a `transition_to_state` call.
         */
        void on_exit() {}

        /*
            Overload this function to process specific events. Override this
            function if you want to handle generic events.

            Either way, return `true` if the event was processed. Return `false`
            if it was not, so the parent state can get a shot.
         */
        bool on_event(Event & const event)
        {
            return false;
        }

        /*
            Returns the current active state.
         */
        State * active_state();

        /*
            Find the common parent with state `other`.
         */
        State * find_common_parent(State * const other);

        char const * const m_name;
        State * m_active_state;
        State * m_parent_state;
    };

    /*
        Base class for events to be processed by state machine states.
     */
    class Event
    {

    };

    /*
        Illegal state transition error.
     */
    class BadStateException
    {
    public:
        BadStateException() : m_state(nullptr) {}
        BadStateException(char const * const state) : m_state(state) {}

        char const * const m_state;
    };
}
