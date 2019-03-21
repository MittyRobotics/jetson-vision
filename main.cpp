#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <zconf.h>
#include "vision/Pipeline.hpp"
#include "vision/PipelineData.hpp"
#include "sockets/SocketConnection.hpp"
#include "threading/SocketThread.hpp"
#include "threading/ProcessThread.hpp"

int main() {
	ProcessThread processThread;

	cv::VideoCapture vc = cv::VideoCapture(0);
	cv::Mat frame;

	while (vc.read(frame)) {
		processThread.frame = frame;
		processThread.taskPending = true;
		usleep(25 * 1000);
	}

	std::cout << "Thread 1 Dead" << std::endl;

    return 1;
}
