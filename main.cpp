#include <stdio.h>
#include <opencv2/opencv.hpp>

int main() {
	cv::Mat mat = cv::imread("../image2New.jpeg");

	cv::imwrite("../imageOutput.jpeg",mat);
	return 0;
}