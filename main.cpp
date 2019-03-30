#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <zconf.h>
#include "threading/SocketThread.hpp"
#include "threading/ProcessThread.hpp"

int main() {
	const Pipeline pipeline = Pipeline();
	const SocketConnection socket;

	cv::VideoCapture vc = cv::VideoCapture(0);
	vc.set(CV_CAP_PROP_AUTO_EXPOSURE, 0.25);
	vc.set(CV_CAP_PROP_EXPOSURE, 0);
	vc.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	vc.set(CV_CAP_PROP_FRAME_HEIGHT, 360);

	cv::Mat frame;

	while (vc.read(frame)) {
		PipelineData data = pipeline.pipeline(frame);
		if (!data.populated) {
			data.data.setDistance(0.0);
		}
		socket.sendData(data.data);
	}

	std::cout << "Failed" << std::endl;

	return 1;
}
