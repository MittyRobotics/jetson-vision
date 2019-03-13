

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Filters.h"
#include "Pipeline.h"

#include <ctime>


int main()
{
	//Start clock
	std::clock_t c_start = std::clock();
	

	cv::Mat image;

	image = cv::imread("C:\\Users\\Owen Leather\\Pictures\\image2New.jpeg");
	

	image = pipeline(image);

	//Calculate process time
	std::clock_t c_end = std::clock();
	long double time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
	std::cout << "CPU time used: " << time_elapsed_ms << " ms\n";


	cv::imshow("Window", image);

	cv::waitKey();
	

	return 0;
}
