#include "pch.h"
#include "Detection.h"


std::vector<std::vector<cv::Point>> detectContour(cv::Mat img) {
	std::vector<std::vector<cv::Point>> ctr;
	cv::findContours(img,ctr, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	return(ctr);
}

std::vector<cv::Point> getApproxPoly(std::vector<std::vector<cv::Point>> ctr) {

	for (int i = 0; i < ctr.size(); i++) {
		std::vector<cv::Point> approxPoly;
		approxPolyDP(ctr[i], approxPoly, 0.04 * arcLength(ctr, true), true);
	}
	
	return(approxPoly);
}