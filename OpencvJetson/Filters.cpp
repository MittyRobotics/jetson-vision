#include "pch.h"
#include "Filters.h"
#include "ColorConstants.h"
#include <iostream>

cv::Mat filterColor(cv::Mat img) {
	cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
	cv::inRange(img,GREEN_MIN_HSV,GREEN_MAX_HSV, img);
	return(img);
}

std::vector<std::vector<cv::Point>> filterSize(std::vector<std::vector<cv::Point>> ctr, int minHeight, int maxHeight) {
	std::vector<std::vector<cv::Point>> newCtr;
	for (int i = 0; i < ctr.size(); i++) {
		cv::Rect boundrectNew = cv::boundingRect(cv::Mat(ctr[i]));
		if (boundrectNew.height > minHeight &&  boundrectNew.height < maxHeight) {
			newCtr.push_back(ctr[i]);
		}

	}
	ctr.clear();
	return(newCtr);
}