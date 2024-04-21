# Threading module CMake file for Qt 6

# Add header files
set(HEADER_FILES
    threadmanager.h
    managedtask.h
)

# Add source files
set(SOURCE_FILES
    threadmanager.cpp
    managedtask.cpp
)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find the QtCore library from Qt 6
find_package(Qt6 COMPONENTS Core REQUIRED)

# Define the threading library with both source and header files
add_library(threading
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

# Link against the QtCore module from Qt 6
target_link_libraries(threading Qt6::Core)

# Include directories
target_include_directories(threading PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
