#ifndef VISION_TARGET_H
#define VISION_TARGET_H

#include <opencv2/core/types.hpp>

struct Target {
	std::vector<cv::Point> leftTarget;
	std::vector<cv::Point> rightTarget;

public:
	int getAngle() const;
};

#endif //VISION_TARGET_H
