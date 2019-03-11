#include <stdio.h>
#include <opencv2/opencv.hpp>

int main() {
	cv::cuda::GpuMat gpuMat = cv::cuda::GpuMat();
	cv::Mat mat = cv::Mat();
	gpuMat.upload(mat);

	// TODO Some Processing

	gpuMat.download(mat);
	std::cout << mat << std::endl;
	return 0;
}