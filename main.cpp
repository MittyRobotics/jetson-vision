#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "vision/Pipeline.h"

int main() {
    Pipeline pipeline;
	//cv::Mat mat = cv::imread("../image2New.jpeg");
	//cv::imwrite("../imageOutput.jpeg",mat);

    //Start clock
    std::clock_t c_start = std::clock();


    cv::Mat image;

    image = cv::imread("../PerspectiveTarget1.jpeg");


    image = pipeline.pipeline(image);

    //Calculate process time
    std::clock_t c_end = std::clock();
    long double time_elapsed_ms = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    std::cout << "CPU time used: " << time_elapsed_ms << " ms\n";

    cv::imwrite("/home/owen/imageOutputNew1.jpeg",image);


    return 0;
}