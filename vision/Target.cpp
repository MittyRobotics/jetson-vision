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
	return xOffset / (imgWidth/2);
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

    double leftOffset = getOffset(leftDistance, leftYaw);
    double rightOffset = getOffset(rightDistance, rightYaw);

    cv::Point lPoint = cv::Point(leftOffset, leftDistance);
    cv::Point rPoint = cv::Point(rightOffset, rightDistance);

    double legO = abs(lPoint.y - rPoint.y);
    double legA = abs(lPoint.x - rPoint.x);
    double skew = (atan(legO / legA)) * (180/3.14159);
    cv::Point mdPt = (lPoint + rPoint)/2;

    double targetDistFromPoint = 2;


    cv::Point driveToPoint;
    cv::Point currentMdPt;
    double turnAngle1;
    double driveDist1;
    double turnAngle2;
    double driveDist2;
    if (leftDistance > rightDistance) {
        driveToPoint = cv::Point((mdPt.x) + legO * targetDistFromPoint, mdPt.y - legA * targetDistFromPoint);
        currentMdPt = cv::Point(mdPt.x, mdPt.y);
    } else {
        driveToPoint =  cv::Point((mdPt.x) + legO * targetDistFromPoint, mdPt.y - legA * targetDistFromPoint);
        currentMdPt =  cv::Point(mdPt.x, mdPt.y);
    }

    //if(Math.abs(angle) > 3 && Math.abs((lYaw + rYaw)/2 ) >  3){
    double angleI1 = 90;
    double slope1 = driveToPoint.y / driveToPoint.x;
    double angleI2 = (atan(slope1))*(180/3.14159);

    turnAngle1 = angleI1 - angleI2;
    if (turnAngle1 > 90) {
        turnAngle1 = 180 - turnAngle1;
    }



    double x1 = (driveToPoint.x -= 0);
    double y1 = (driveToPoint.y -= 0);
    driveDist1 = sqrt(x1 * x1 + y1 * y1);

    double angleI3 = (atan(slope1)) * (180/3.14159);
    double slope2 = (currentMdPt.y - driveToPoint.y) / (currentMdPt.x - driveToPoint.x);
    double angleI4 = (atan(slope2)) * (180/3.14159);

    turnAngle2 = angleI3 - angleI4;

    if (turnAngle2 > 90) {
        turnAngle2 = 180 - turnAngle2;
    }

    turnAngle2 = -turnAngle2;

    if (leftDistance > rightDistance) {
        turnAngle1 = -turnAngle1;
        turnAngle2 = -turnAngle2;
    }

    x1 = (driveToPoint.x -= currentMdPt.x);
    y1 = (driveToPoint.y -= currentMdPt.y);
    driveDist2 = sqrt(x1 * x1 + y1 * y1)  - 10;

    angle = turnAngle1;
    distance = driveDist1;
    angle1 = turnAngle2;
    distance1 = driveDist2;
}

void Target::setDistance(double d) {
	distance = d;
}

void Target::setDistance1(double d) {
    distance1 = d;
}

double Target::getOffset(double dist, double yaw) {
    double offset = abs(dist * tan((yaw) * 3.15159/180));
    if (yaw < 0) {
        offset = -offset;
    }
    return (offset);
}
