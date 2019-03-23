#include <cv.hpp>
#include "Target.hpp"

const double TARGET_HEIGHT = 5.5;
const double CALC_FOCAL_LENGTH = 571;
const double imgWidth = 320;

double getDiagonalDistance(double targetPixelHeight) {
	return (TARGET_HEIGHT * CALC_FOCAL_LENGTH) / targetPixelHeight;
}

double getYaw(int xPos, double imgWidth) {
	double xOffset = (imgWidth / 2) - xPos;
	double yaw = atan2(xOffset, CALC_FOCAL_LENGTH);
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

	const double leftYaw = getYaw(leftRect.boundingRect().x, imgWidth / 2);
	const double rightYaw = getYaw(leftRect.boundingRect().x, imgWidth / 2);
	angle = (leftYaw + rightYaw) / 2;
}
