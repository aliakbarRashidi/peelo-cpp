project("peelo-cpp" CXX)
cmake_minimum_required(VERSION 2.8.7)

include(CheckCXXCompilerFlag)
include(CheckCXXSymbolExists)
include(CheckIncludeFileCXX)

check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()

check_include_file_cxx(cstdint PEELO_HAVE_CSTDINT)
check_include_file_cxx(stdint.h PEELO_HAVE_STDINT_H)

check_cxx_symbol_exists(vasprintf cstdarg PEELO_HAVE_VASPRINTF)
check_cxx_symbol_exists(vsnprintf cstdarg PEELO_HAVE_VSNPRINTF)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config.hpp.in
  ${CMAKE_CURRENT_SOURCE_DIR}/include/peelo/config.hpp
)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
link_directories(${LIBRARY_OUTPUT_PATH})

add_library(
    peelo-cpp
    src/chrono/date.cpp
    src/chrono/datetime.cpp
    src/chrono/duration.cpp
    src/chrono/month.cpp
    src/chrono/time.cpp
    src/chrono/weekday.cpp
    src/io/filename.cpp
    src/io/filepath.cpp
    src/net/uri.cpp
    src/number/complex.cpp
    src/number/ratio.cpp
    src/text/rune.cpp
    src/text/string.cpp
    src/text/stringbuilder.cpp
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/peelo
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)
install(
    TARGETS peelo-cpp ARCHIVE DESTINATION lib
)

enable_testing()
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/test TEST_SRCS)
foreach(i ${TEST_SRCS})
    get_filename_component(name ${i} NAME_WE)
    add_executable(${name} ${i})
    target_link_libraries(${name} peelo-cpp)
    add_test(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
    add_dependencies(${name} peelo-cpp)
endforeach()
