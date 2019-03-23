#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <zconf.h>
#include "threading/SocketThread.hpp"
#include "threading/ProcessThread.hpp"

int main() {
	ProcessThread processThread;

	cv::VideoCapture vc = cv::VideoCapture(0);
	vc.set(CV_CAP_PROP_AUTO_EXPOSURE, 0.25);
	vc.set(CV_CAP_PROP_EXPOSURE, 0);
	vc.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	vc.set(CV_CAP_PROP_FRAME_HEIGHT, 360);

	cv::Mat frame;

	while (vc.read(frame)) {
		processThread.frame = frame;
		processThread.taskPending = true;
		usleep(25 * 1000);
	}

	return 1;
}
