cmake_minimum_required(VERSION 3.5)
project(vision)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(vision main.cpp vision/Drawing.cpp vision/Drawing.h vision/Detection.cpp vision/Detection.h vision/Filters.cpp vision/Filters.h vision/Pipeline.cpp vision/Pipeline.h vision/Target.h vision/Math.cpp vision/Math.h)
target_link_libraries(vision ${OpenCV_LIBS})
