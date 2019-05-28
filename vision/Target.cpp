#include "Target.hpp"
#include <cv.hpp>
#include <math.h>

const double TARGET_HEIGHT = 5.5;
const double CALC_FOCAL_LENGTH = 571;
const double imgWidth = 640;

double Target::getDiagonalDistance(double targetPixelHeight) {
	return (TARGET_HEIGHT * CALC_FOCAL_LENGTH) / targetPixelHeight;
}

double Target::getYaw(int xPos) {
	double xOffset = abs(imgWidth / 2 - xPos);
	double yaw = (atan(xOffset / 570)*180/3.14159);
	if (xPos < imgWidth / 2) {
		yaw = -yaw;
	}
	return (yaw);
}

void Target::calculate() {
	const cv::RotatedRect leftRect = cv::minAreaRect(leftTarget);
	const cv::RotatedRect rightRect = cv::minAreaRect(rightTarget);

	const double leftHeight = leftRect.size.height;
	const double rightHeight = rightRect.size.height;

	const double leftDistance = getDiagonalDistance(leftHeight);
	const double rightDistance = getDiagonalDistance(rightHeight);

	distance = (leftDistance + rightDistance) / 2;

	const double leftYaw = getYaw(leftRect.center.x);
	const double rightYaw = getYaw(rightRect.center.x);

	const double skewGain = 2; //Tune skew gain to get best results
	//Skew value, change to left-right if direction is wrong
	const double skew = ((rightDistance - leftDistance) / 10) * skewGain; //TODO: Calibrate the 10 value based on range of values needed
	//TODO: Add skew value to angle after tuning angle
	angle = ((leftYaw + rightYaw) / 2);
}

void Target::setDistance(double d) {
	distance = d;
}
