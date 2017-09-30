cmake_minimum_required (VERSION 2.8.12)
project(schedule)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -pedantic -std=c++11")

add_executable(schedule "DvcSchedule5.cpp")
