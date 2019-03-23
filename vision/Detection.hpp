#ifndef VISION_DETECTION_H
#define VISION_DETECTION_H

#include "Target.hpp"

class Detection {
public:

	std::vector<std::vector<cv::Point>> detectContour(cv::Mat img);

	std::vector<std::vector<cv::Point>> getApproxPoly(std::vector<std::vector<cv::Point>> ctr);

	Target getClosestTarget(std::vector<std::vector<cv::Point>> ctr, int imageCenter);

};


#endif //VISION_DETECTION_H
