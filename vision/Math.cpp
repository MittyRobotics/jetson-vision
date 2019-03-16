//
// Created by Owen Leather on 3/16/2019.
//

#include <opencv2/opencv.hpp>
#include "Math.hpp"

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
    //Get relative target offset
    double leftOffset = getRelativeOffset(leftDistance, leftYaw);
    double rightOffset = getRelativeOffset(rightDistnce, rightYaw);
    double offset = getRelativeOffset(targetDistance, targetYaw);
    //Get direct distance to target
    double directDistance = sqrt((offset*offset) + (targetDistance * targetDistance));
    //Get target legs
    double oLeg = leftDistance-rightDistnce;
    double aLeg = leftOffset-rightOffset;
    //Get drive to point
    double driveToX = offset + oLeg;
    double driveToY = targetDistance - aLeg;
    //Get new dist and angle
    double newDist = sqrt((driveToX*driveToX) + (driveToY * driveToY));
    double newAngle = atan(driveToX / driveToY);



    std::string distAndYaw = "d" + std::to_string(newDist) +  "a" + std::to_string(newAngle);
    return distAndYaw;

}

double Math::getRelativeOffset(double targetDistance, double yaw) {
    return (targetDistance * tan(yaw));
}

double Math::getDiagonalDistance(double targetPixelHeight) {
    return ((TARGET_HEIGHT * CALC_FOCAL_LENGTH) / targetPixelHeight);
}

double Math::getYaw(int xPos, double imgWidth) {
    double xOffset = (imgWidth / 2) - xPos;
    double yaw = atan2(xOffset, CALC_FOCAL_LENGTH);
    return (yaw);
}
