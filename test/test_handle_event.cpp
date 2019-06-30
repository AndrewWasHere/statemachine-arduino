/*
    Copyright 2019, Andrew Lin.
    
    This source code is released under the 3-Clause BSD license. See
    LICENSE.txt or https://opensource.org/licenses/BSD-3-Clause.
*/
#include <cassert>
#include <iostream>
#include "statemachine.h"

using namespace statemachine;

enum EventId {
    HANDLED_EVENT,
    UNHANDLED_EVENT
};

class HandledEvent : public Event
{
public:
    HandledEvent() : Event(HANDLED_EVENT, "handled") {}
};

class UnhandledEvent : public Event
{
public:
    UnhandledEvent() : Event(UNHANDLED_EVENT, "Unhandled") {}
};

class TestBaseState : public State
{
public:
    TestBaseState(char const * name, State * parent) :
        State(name, parent),
        m_event_handled(false)
    {}
    void reset() { m_event_handled = false; }

    bool m_event_handled;

protected:
    bool on_event(Event & event) override
    {
        bool handled = false;

        switch(event.m_id)
        {
            case HANDLED_EVENT:
                handled = on_event(dynamic_cast<HandledEvent &>(event));
                break;
            case UNHANDLED_EVENT:
                handled = on_event(dynamic_cast<UnhandledEvent &>(event));
                break;
            default:
                break;
        }
        return handled;
    }

    virtual bool on_event(HandledEvent & event) { return false; }
    virtual bool on_event(UnhandledEvent & event) { return false; }

};

class MachineState : public TestBaseState
{
public:
    MachineState(char const * name, State * parent) :
        TestBaseState(name, parent)
    {}

protected:
    bool on_event(HandledEvent & event) override
    {
//        std::cout << m_name << " processed HandledEvent." << std::endl;
        m_event_handled = true;
        return true;
    }
    bool on_event(UnhandledEvent & event) override
    {
//        std::cout << m_name << " processed UnhandledEvent." << std::endl;
        m_event_handled = true;
        return true;
    }
};

class TestState : public TestBaseState
{
public:
    TestState(char const * name, State * parent) : TestBaseState(name, parent) {}

protected:
    bool on_event(HandledEvent & event) override
    {
//        std::cout << m_name << " processed HandledEvent." << std::endl;
        m_event_handled = true;
        return true;
    }
};

void test_handled_event()
{
    std::cout << "test_handled_event()..." << std::endl;

    MachineState machine("machine", nullptr);
    TestState s("s", &machine);
    HandledEvent e;

    machine.transition_to_state(&s);
    machine.handle_event(e);

    assert(s.m_event_handled);
    assert(!machine.m_event_handled);
}

void test_unhandled_event()
{
    std::cout << "test_unhandled_event()..." << std::endl;

    MachineState machine("machine", nullptr);
    TestState s("s", &machine);
    UnhandledEvent e;

    machine.transition_to_state(&s);
    machine.handle_event(e);

    assert(!s.m_event_handled);
    assert(machine.m_event_handled);
}
