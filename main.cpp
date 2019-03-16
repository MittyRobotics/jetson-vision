#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "vision/Pipeline.hpp"
#include "sockets/SocketConnection.hpp"

int main() {
    Pipeline pipeline;
    SocketConnection socket;

	cv::VideoCapture cap = cv::VideoCapture(0);
	cap.set(CV_CAP_PROP_AUTO_EXPOSURE, 0.25);
	cap.set(CV_CAP_PROP_EXPOSURE, -100);
	cap.set(CV_CAP_PROP_BRIGHTNESS, 0);

	cv::Mat image;
	while (cap.read(image)){
		TargetData data = pipeline.pipeline(image);
		socket.sendDistance(data.distance);
		socket.sendAngle(data.angle);
		return -1;
	}

    return 0;
}