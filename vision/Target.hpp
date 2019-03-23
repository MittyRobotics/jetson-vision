#ifndef VISION_TARGET_H
#define VISION_TARGET_H

#include <opencv2/core/types.hpp>

class Target {
public:
	Target() {
		this->leftTarget = std::vector<cv::Point>();
		this->rightTarget = std::vector<cv::Point>();
	}
	Target(const std::vector<cv::Point> &leftTarget, const std::vector<cv::Point> &rightTarget) {
		this->leftTarget = leftTarget;
		this->rightTarget = rightTarget;
	}

public:
	std::vector<cv::Point> leftTarget;
	std::vector<cv::Point> rightTarget;

public:
	void calculate();

public:
	double getAngle() const {
		return angle;
	}

	double getDistance() const {
		return distance;
	}

private:
	double angle = 1337;
	double distance = 1337;
};

#endif //VISION_TARGET_H
