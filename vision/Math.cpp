//
// Created by Owen Leather on 3/16/2019.
//

#include <opencv2/opencv.hpp>
#include "Math.h"

std::string Math::getDistanceAndAngle(Target target, double imgWidth) {
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
    double leftYaw = getYaw(leftRect.boundingRect().x, imgWidth);
    double rightYaw = getYaw(leftRect.boundingRect().x, imgWidth);
    double targetYaw = (leftYaw + rightYaw) /2;

    std::string distAndYaw = "d" + std::to_string(targetDistance) +  "a" + std::to_string(targetYaw);
    return distAndYaw;

}

double Math::getDiagonalDistance(double targetPixelHeight) {
    return ((TARGET_HEIGHT * CALC_FOCAL_LENGTH) / targetPixelHeight);
}

double Math::getYaw(int xPos, double imgWidth) {
    double xOffset = (imgWidth / 2) - xPos;
    double yaw = atan2(xOffset, CALC_FOCAL_LENGTH);
    return (yaw);
}
