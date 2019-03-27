#include "Target.hpp"
#include <cv.hpp>

const double TARGET_HEIGHT = 5.5;
const double CALC_FOCAL_LENGTH = 571;
const double imgWidth = 640;

double Target::getDiagonalDistance(double targetPixelHeight) {
	return (TARGET_HEIGHT * CALC_FOCAL_LENGTH) / targetPixelHeight;
}

double Target::getYaw(int xPos) {
	double xOffset = xPos - (imgWidth / 2);
	return xOffset / imgWidth;
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
	angle = (leftYaw + rightYaw) / 2;
}

void Target::setDistance(double d) {
	distance = d;
}
