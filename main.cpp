#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "vision/Pipeline.hpp"
#include "vision/PipelineData.hpp"
#include "sockets/SocketConnection.hpp"

int main() {
    Pipeline pipeline;
    //SocketConnection socket;
	clock_t tStart = clock();
	//cv::VideoCapture cap = cv::VideoCapture(0);
	//cap.set(CV_CAP_PROP_AUTO_EXPOSURE, 0.25);
	//cap.set(CV_CAP_PROP_EXPOSURE, -100);
	//cap.set(CV_CAP_PROP_BRIGHTNESS, 0);

	cv::Mat image = cv::imread("../PerspectiveTarget1.jpeg");

//	while (cap.read(image)){
		PipelineData data = pipeline.pipeline(image);
		std::cout << data.data << std::endl;


//		socket.send(data.data.c_str());
//	}
	printf("Time taken: %.2fms\n", (double)(clock() - tStart)/CLOCKS_PER_SEC * 1000);

    return 0;
}