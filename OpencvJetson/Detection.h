#pragma once
#include "pch.h"
#include <opencv2/opencv.hpp>

std::vector<std::vector<cv::Point>> detectContour(cv::Mat img);

std::vector<cv::Point> getApproxPoly(std::vector<std::vector<cv::Point>> ctr);
