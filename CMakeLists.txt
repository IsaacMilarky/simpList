cmake_minimum_required(VERSION 2.4)

project(simpList)

include_directories(${simpList})
add_executable(app main.cpp ListItem.cpp priorityTodoQueue.cpp)
