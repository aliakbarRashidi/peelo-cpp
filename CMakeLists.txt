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
    src/io/filename.cpp
    src/net/uri.cpp
    src/text/rune.cpp
    src/text/string.cpp
)

INSTALL(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/peelo
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)
INSTALL(
    TARGETS peelo-cpp ARCHIVE DESTINATION lib
)

ENABLE_TESTING()
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/test TEST_SRCS)
FOREACH(i ${TEST_SRCS})
    GET_FILENAME_COMPONENT(name ${i} NAME_WE)
    SET(name "test_${name}")
    ADD_EXECUTABLE(${name} ${i})
    TARGET_LINK_LIBRARIES(${name} peelo-cpp)
    ADD_TEST(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
    ADD_DEPENDENCIES(${name} peelo-cpp)
ENDFOREACH()
