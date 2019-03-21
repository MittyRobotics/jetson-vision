cmake_minimum_required(VERSION 3.5)
project(vision C CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(Threads)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(vision main.cpp
        vision/Drawing.cpp vision/Drawing.hpp vision/Detection.cpp vision/Detection.hpp vision/Filters.cpp vision/Filters.hpp vision/Pipeline.cpp vision/Pipeline.hpp vision/Target.hpp vision/Math.cpp vision/Math.hpp vision/PipelineData.hpp
        sockets/SocketConnection.hpp sockets/SocketConnection.cpp
        threading/Thread.cpp threading/Thread.hpp threading/SocketThread.cpp threading/SocketThread.hpp threading/ProcessThread.cpp threading/ProcessThread.hpp)
target_link_libraries(vision ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})
