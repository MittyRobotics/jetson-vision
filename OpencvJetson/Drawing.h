#pragma once
#include "pch.h"
#include <opencv2/opencv.hpp>

cv::Mat drawContours(cv::Mat img, std::vector<std::vector<cv::Point>> ctr);