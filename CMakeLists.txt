CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(peelo-cpp)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

ADD_LIBRARY(
    peelo-cpp
    src/chrono/date.cpp
    src/chrono/datetime.cpp
    src/chrono/time.cpp
)