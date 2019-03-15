//
// Created by Owen Leather on 3/14/2019.
//

#ifndef VISION_TARGET_H
#define VISION_TARGET_H

#include <opencv2/core/types.hpp>

class Target{
public:
    std::vector<cv::Point> leftTarget;
    std::vector<cv::Point> rightTarget;
};

#endif //VISION_TARGET_H
