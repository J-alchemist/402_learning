cmake_minimum_required(VERSION 2.8)

include_directories(${PROJECT_SOURCE_DIR}/lib/inc)   #Myrw.h
set(SRC_LIST  serverEpoll.c  ${PROJECT_SOURCE_DIR}/lib/wrap.c)
add_executable(serverEpoll  ${SRC_LIST})

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/build/bin)

message(STATUS "this PROJECT_SOURCE_DIR:"${PROJECT_SOURCE_DIR})
message(STATUS "this PROJECT_BINARY_DIR:"${PROJECT_BINARY_DIR})
