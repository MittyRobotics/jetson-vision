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

	void setDistance(double d);

public:
	std::vector<cv::Point> leftTarget;
	std::vector<cv::Point> rightTarget;

public:
	void calculate();

public:
	void setAngle(double value) {
		anglel = value;
	}

	double getAngle() const {
		return anglel;
	}

	double getDistance() const {
		return distancel;
	}
	void setAngler(double value) {
		angler = value;
	}

	double getAngler() const {
		return angler;
	}

	double getDistancer() const {
		return distancer;
	}

private:
	double anglel = 1337;
	double angler = 1337;
	double distancel = 1337;
	double distancer;


private:
	double getDiagonalDistance(double targetPixelHeight);
	double getYaw(int xPos);
};

#endif //VISION_TARGET_H
