enable_testing()

set(SOURCES
  ../src/classes/Instance.cpp
  ../src/classes/Solution.cpp
  ../src/classes/NeighborhoodOperations.cpp
  ../src/classes/DoublyLinkedList.cpp
  ../src/classes/Globals.cpp
)
set(INCLUDES ../src/headers)

add_executable(instance_test instance_test.cpp ${SOURCES})
target_link_libraries(
  instance_test
  GTest::gtest_main
)
target_include_directories(instance_test PUBLIC ${INCLUDES})
add_dependencies(instance_test copy_instances)

add_executable(solution_test solution_test.cpp ${SOURCES})
target_link_libraries(
  solution_test
  GTest::gtest_main
)
target_include_directories(solution_test PUBLIC ${INCLUDES})
add_dependencies(solution_test copy_instances)

add_executable(no_test no_test.cpp ${SOURCES})
target_link_libraries(
  no_test
  GTest::gtest_main
)
target_include_directories(no_test PUBLIC ${INCLUDES})
add_dependencies(no_test copy_instances)

add_executable(dll_test dll_test.cpp ${SOURCES})
target_link_libraries(
  dll_test
  GTest::gtest_main
)
target_include_directories(dll_test PUBLIC ${INCLUDES})
add_dependencies(dll_test copy_instances)

include(GoogleTest)
gtest_discover_tests(instance_test)
gtest_discover_tests(solution_test)
gtest_discover_tests(no_test)
gtest_discover_tests(dll_test)
