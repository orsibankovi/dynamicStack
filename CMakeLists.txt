cmake_minimum_required(VERSION 3.23)
project(dynamicStack)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")

add_executable(dynamicStack main.cpp DynamicStack.h)
