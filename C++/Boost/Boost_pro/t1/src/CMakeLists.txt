cmake_minimum_required(VERSION 3.5)

find_package(Boost 1.6 REQUIRED COMPONENTS system thread filesystem date_time)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
add_definitions(${Boost_DEFINITIONS})

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)

set(SRC_LIST funobj.cpp)
add_executable(funobj ${SRC_LIST})

target_link_libraries(funobj ${Boost_LIBRARIES})

message(STATUS "this build    dir: " ${PROJECT_BINARY_DIR})
message(STATUS "this projects dir: " ${PROJECT_SOURCE_DIR})
