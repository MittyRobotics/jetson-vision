cmake_minimum_required(VERSION 3.5)
project(vision)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Threads)

add_executable(vision main.cpp
        vision/Pipeline.cpp vision/Pipeline.hpp vision/Target.hpp vision/PipelineData.hpp
        sockets/SocketConnection.hpp sockets/SocketConnection.cpp
        threading/Thread.cpp threading/Thread.hpp threading/SocketThread.cpp threading/SocketThread.hpp threading/ProcessThread.cpp threading/ProcessThread.hpp vision/Target.cpp threading/SelectingThread.cpp threading/SelectingThread.hpp)
target_link_libraries(vision ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})
