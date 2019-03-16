//
// Created by Owen Leather on 3/16/2019.
//

#include <opencv2/opencv.hpp>
#include "Math.h"

std::string Math::getDistanceAndAngle(Target target) {
    //Get left and right diagonal heights
    cv::RotatedRect leftRect = cv::minAreaRect(target.leftTarget);
    cv::RotatedRect rightRect = cv::minAreaRect(target.rightTarget);
    double leftHeight = leftRect.size.height;
    double rightHeight = rightRect.size.height;
    //Get left and right distance
    double leftDistance = getDiagonalDistance(leftHeight);
    double rightDistnce = getDiagonalDistance(rightHeight);
    //Get average distance to target
    double targetDistance = (leftDistance + rightDistnce) / 2;
    //Get yaw to target


    return std::__cxx11::string();

}

double Math::getDiagonalDistance(double targetPixelHeight) {
    return ((TARGET_HEIGHT * CALC_FOCAL_LENGTH) / targetPixelHeight);
}

double Math::getYaw(int xPos, double imgWidth) {
    double xOffset = abs(imgWidth / 2 - cPos);
    double yaw = toDegrees(atan(xOffset / CALC_FOCAL_LENGTH));
    if (xPos < imgWidth / 2) {
        yaw = -yaw;
    }
    return (yaw);
}
