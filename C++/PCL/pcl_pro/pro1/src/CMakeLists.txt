cmake_minimum_required(VERSION 3.5)

find_package(PCL REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
	
message(STATUS "binary dir: " ${PROJECT_BINARY_DIR})
message(STATUS "source dir: " ${PROJECT_SOURCE_DIR})

set(SRC_LIST octreepcl.cpp)
add_executable(octreepcl ${SRC_LIST})

target_link_libraries(octreepcl ${PCL_LIBRARIES})

