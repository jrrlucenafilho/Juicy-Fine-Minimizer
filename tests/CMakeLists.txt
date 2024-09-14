enable_testing()

set(SOURCES
  ../src/classes/Instance.cpp
  ../src/classes/Solution.cpp
)
set(INCLUDES ../src/headers)

add_executable(instance_test instance_test.cpp ${SOURCES})
target_link_libraries(
  instance_test
  GTest::gtest_main
)
target_include_directories(instance_test PUBLIC ${INCLUDES})
add_dependencies(instance_test copy_instances)

include(GoogleTest)
gtest_discover_tests(instance_test)
