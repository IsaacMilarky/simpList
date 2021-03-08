cmake_minimum_required(VERSION 3.10)

#Set the project name
project(SimpList VERSION 0.01)

#This part was not explained well in the tutorial.
configure_file(
    "${PROJECT_SOURCE_DIR}/SimpListConfig.h.in"
    "${PROJECT_SOURCE_DIR}/SimpListConfig.h")

#C++ 11
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

#add_executable(SimpList main.cpp)

set(CMAKE_BUILD_TYPE Debug)
#Hmm, today I will try to compile a boost library (clueless)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.75.0 COMPONENTS serialization filesystem)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(SimpList ListItem.cpp priorityTodoQueue.cpp ListItemLoadWrapper.cpp TodoController.cpp main.cpp)
    target_link_libraries(SimpList ${Boost_LIBRARIES})
endif()

target_include_directories(SimpList PUBLIC
                            "{PROJECT BINARY_DIR}")