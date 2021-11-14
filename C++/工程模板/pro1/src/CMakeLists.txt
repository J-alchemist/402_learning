cmake_minimum_required(VERSION 3.5)

#set(CMAKE_CXX_COMPILER "g++") 
#set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories(${PROJECT_SOURCE_DIR}/inc)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)

set(SRC_LIST main.cpp myc++class.cpp)
add_executable(main ${SRC_LIST})

message(STATUS "this build    dir: " ${PROJECT_BINARY_DIR})
message(STATUS "this projects dir: " ${PROJECT_SOURCE_DIR})
