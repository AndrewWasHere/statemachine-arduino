/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "statemachine.h"

namespace statemachine
{
    State::State(char const * const name, State * const parent) :
        m_name(name),
        m_active_state(nullptr),
        m_parent_state(parent)
    {}

    void State::transition_to_state(State * const state)
    {
        State * s = active_state();
        State * common_parent = s->find_common_parent(state);

        if (!common_parent)
        {
            throw BadStateException(state->m_name);
        }

        // Call on_exit() from active state to common parent.
        for (; s != common_parent->m_parent_state; s = s->m_parent_state)
        {
            s->on_exit();
        }

        // Update active state pointers from common parent to `state`.
        for (s = state; s != common_parent; s = s->m_parent_state)
        {
            s->m_parent_state->m_active_state = s;
        }

        // Call on_entry from common parent's active state to `state`.
        for (s = common_parent->m_active_state; s; s = s->m_active_state)
        {
            s->on_entry();
        }
    }

    void State::handle_event(Event & event)
    {
        for (
            State * s = active_state(); 
            s and s->on_event(event); 
            s = s->m_parent_state
        )
            ;
    }

    char const * const State::active_state_name()
    {
        return active_state()->m_name;
    }

    State * State::active_state()
    {
        State * s = this;
        while (this->m_active_state) {
            s = this->m_active_state;
        }

        return s;
    }

    /*
        Find the common parent with `rhs`.
     */
    State * State::find_common_parent(State * const rhs)
    {
        for (State * l = this; l; l = l->m_parent_state)
        {
            for (State * r = rhs; r; r = r->m_parent_state)
            {
                if (r == l)
                {
                    // Common parent found.
                    return r;
                }
            }
        }

        // No common parent.
        return nullptr;
    }

}