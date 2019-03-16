//
// Created by Owen Leather on 3/16/2019.
//

#ifndef VISION_MATH_H
#define VISION_MATH_H


#include <string>
#include "Target.hpp"

class Math {
public:
    //Constants
    double TARGET_HEIGHT = 5.5;
    double CALC_FOCAL_LENGTH = 571;

     std::string getDistanceAndAngle(Target target, double imgWidth);


     double getDiagonalDistance(double targetPixelHeight);

     double getYaw(int xPos, double imgWidth);

     double getRelativeOffset(double targetDistance, double yaw);
};


#endif //VISION_MATH_H
