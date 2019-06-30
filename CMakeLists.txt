cmake_minimum_required(VERSION 3.10)
project(finitestatemachine LANGUAGES CXX)

# State machine library.
add_subdirectory(statemachine)

# Test application.
add_subdirectory(test)
