cmake_minimum_required(VERSION 3.29)
project(CPP2_s21_containers_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)
include_directories(
        src
        src/containers
        src/containers/array
        src/containers/stack
        src/containers/queue
        ${GTEST_INCLUDE_DIRS}
)

add_executable(ArrayTests
        src/containers/array/array_tests.cpp
        src/containers/array/s21_array.h
)
add_executable(StackTests
        src/containers/stack/s21_stack.h
        src/containers/stack/stack_tests.cpp
)
add_executable(QueueTests
        src/containers/queue/s21_queue.h
        src/containers/queue/queue_tests.cpp
)

target_link_libraries(ArrayTests ${GTEST_LIBRARIES} pthread)
target_link_libraries(StackTests ${GTEST_LIBRARIES} pthread)
target_link_libraries(QueueTests ${GTEST_LIBRARIES} pthread)

