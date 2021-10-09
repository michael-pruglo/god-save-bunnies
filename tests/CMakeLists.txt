project(tests)

# '.lib' is the folder with Google Test sources
add_subdirectory(.lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests ../src/types.hpp ../src/Random.hpp ../src/Random.cpp ../src/ColonySimulator.hpp ../src/ColonySimulator.cpp ../src/utility/DoublyLinkedList.hpp ListTests.cpp)
target_link_libraries(tests gtest gtest_main)
