set(
    source 
    main.cpp 
    test_construction.cpp
    test_handle_event.cpp
    test_on_initialize.cpp
    test_transition_to_state.cpp
    test_transition_to_history.cpp
    test_transition_to_deep_history.cpp
)
add_executable(statemachine_tests ${source})
target_include_directories(
    statemachine_tests PUBLIC 
    ${CMAKE_SOURCE_DIR}/statemachine
)
target_link_libraries(statemachine_tests PRIVATE statemachine)