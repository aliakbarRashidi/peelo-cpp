CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("peelo-cpp" CXX)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})

ADD_LIBRARY(
    peelo-cpp
    src/chrono/date.cpp
    src/chrono/datetime.cpp
    src/chrono/duration.cpp
    src/chrono/month.cpp
    src/chrono/time.cpp
    src/chrono/weekday.cpp
    src/net/uri.cpp
    src/text/rune.cpp
    src/text/string.cpp
)

INSTALL(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)
INSTALL(
    TARGETS peelo-cpp ARCHIVE DESTINATION lib
)
