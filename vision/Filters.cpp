//
// Created by Owen Leather on 3/14/2019.
//

#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Filters.hpp"

cv::Scalar GREEN_MIN_HSV = cv::Scalar(50, 105, 0);
cv::Scalar GREEN_MAX_HSV = cv::Scalar(180, 255, 255);

cv::Mat Filters::filterColor(cv::Mat img) {
    cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
    cv::inRange(img,GREEN_MIN_HSV,GREEN_MAX_HSV, img);
    return img;
}

std::vector<std::vector<cv::Point>> Filters::filterSize(std::vector<std::vector<cv::Point>> ctr, int minHeight, int maxHeight) {
    std::vector<std::vector<cv::Point>> newCtr;
    for (int i = 0; i < ctr.size(); i++) {
        cv::Rect boundrectNew = cv::boundingRect(cv::Mat(ctr[i]));
        if (boundrectNew.height > minHeight &&  boundrectNew.height < maxHeight) {
            newCtr.push_back(ctr[i]);
        }
    }
    ctr.clear();
    return newCtr;
}

std::vector<std::vector<cv::Point>> Filters::filterVerts(std::vector<std::vector<cv::Point>> ctr, int vertCount) {
    std::vector<std::vector<cv::Point>> newCtr;

    for (int i = 0; i < ctr.size(); i++) {

        if(ctr[i].size() == vertCount){

            newCtr.push_back(ctr[i]);
        }

    }
    ctr.clear();
    return newCtr;
}
