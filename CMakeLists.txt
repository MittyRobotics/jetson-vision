cmake_minimum_required(VERSION 3.5)
project(vision)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(vision main.cpp vision/Drawing.cpp vision/Drawing.hpp vision/Detection.cpp vision/Detection.hpp vision/Filters.cpp vision/Filters.hpp vision/Pipeline.cpp vision/Pipeline.hpp vision/Target.hpp vision/Math.cpp vision/Math.hpp vision/PipelineData.hpp)
target_link_libraries(vision ${OpenCV_LIBS})
