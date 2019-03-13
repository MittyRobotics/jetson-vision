#pragma once
#include "pch.h"
#include <opencv2/opencv.hpp>
cv::Mat filterColor(cv::Mat img);
std::vector<std::vector<cv::Point>> filterSize(std::vector<std::vector<cv::Point>> ctr, int minHeight, int maxHeight);