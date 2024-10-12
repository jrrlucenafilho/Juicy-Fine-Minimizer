# Added the source files
add_executable(${PROJECT_NAME} main.cpp 
    classes/Instance.cpp 
    classes/Solution.cpp 
    classes/NeighborhoodOperations.cpp
    classes/DoublyLinkedList.cpp
)

# Added include directories
target_include_directories(${PROJECT_NAME} PUBLIC headers)

# Copy the instances to be used in the build
add_dependencies(${PROJECT_NAME} copy_instances)
