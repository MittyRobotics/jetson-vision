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
    void setDistance1(double d);

public:
	std::vector<cv::Point> leftTarget;
	std::vector<cv::Point> rightTarget;

public:
	void calculate();

public:
	void setAngle(double value) {
		angle = value;
	}
    void setAngle1(double value) {
        angle1 = value;
    }
	double getAngle() const {
		return angle;
	}

	double getDistance() const {
		return distance;
	}
    double getAngl1e() const {
        return angle1;
    }

    double getDistance1() const {
        return distance1;
    }

private:
	double angle = 1337;
	double distance = 1337;
	double angle1 = 1337;
	double distance1 = 1337;

private:
	double getDiagonalDistance(double targetPixelHeight);
	double getYaw(int xPos);
	double getOffset(double dist, double yaw);
};

#endif //VISION_TARGET_H
