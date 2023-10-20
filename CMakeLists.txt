cmake_minimum_required(VERSION 3.21)

project(algorithms)
set(CMAKE_CXX_STANDARD 20)

# => GOOGLE TESTS
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()
# => GOOGLE TESTS

add_executable(algo_test test/vector_test.cpp test/skiplist_set_test.cpp test/dlist_test.cpp test/block_storage_test.cpp test/array_stack_test.cpp test/array_deque_test.cpp)
target_link_libraries(algo_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(algo_test)
