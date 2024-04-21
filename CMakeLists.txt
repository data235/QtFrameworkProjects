cmake_minimum_required(VERSION 3.14)

project(QtFrameworkProjects VERSION 1.0 DESCRIPTION "Qt-based Framework for Various Projects")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QT specific settings
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Add subdirectories
add_subdirectory(core)
