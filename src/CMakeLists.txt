# Added the source files
add_executable(${PROJECT_NAME} main.cpp classes/Instance.cpp classes/Solution.cpp)

# Added include directories
target_include_directories(${PROJECT_NAME} PUBLIC headers)
