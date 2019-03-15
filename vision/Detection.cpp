//
// Created by Owen Leather on 3/14/2019.
//

#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Detection.h"

std::vector<std::vector<cv::Point>> Detection::detectContour(cv::Mat img) {
    std::vector<std::vector<cv::Point>> ctr;
    cv::findContours(img, ctr, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    return (ctr);
}

std::vector<std::vector<cv::Point>> Detection::getApproxPoly(std::vector<std::vector<cv::Point>> ctr) {
    std::vector<std::vector<cv::Point>> approxPolys;
    std::vector<cv::Point> approxPoly;

    for (int i = 0; i < ctr.size(); i++) {
        approxPolyDP(ctr[i], approxPoly, 0.04 * arcLength(ctr[i], true), true);
        approxPolys.push_back(approxPoly);
        approxPoly.clear();
    }
    return approxPolys;
}

Target Detection::getClosestTarget(std::vector<std::vector<cv::Point>> ctr, int imageCenter) {
    Target target;
    std::vector<std::vector<cv::Point>> leftCtr;
    std::vector<std::vector<cv::Point>> rightCtr;
    std::vector<std::vector<cv::Point>> groupedTargets;

    for(int i = 0; i < ctr.size(); i++){
        cv::RotatedRect rect = cv::minAreaRect(ctr[i]);
        if (abs(static_cast<int>(rect.angle)) > 45) {
            leftCtr.push_back(ctr[i]);
        }
        else{
            rightCtr.push_back(ctr[i]);
        }
    }

    std::vector<int> curIndexLeft;
    std::vector<int> curIndexRight;
    for(int i = 0; i < leftCtr.size(); i++){
        for(int a = 0; a < rightCtr.size(); a++){
            cv::Rect boundboxLeft = cv::boundingRect(leftCtr[i]);
            cv::Rect boundboxRight = cv::boundingRect(rightCtr[a]);
            if(boundboxLeft.x < boundboxRight.x){
                if(abs(boundboxLeft.x - boundboxRight.x) < (boundboxLeft.height*2 + boundboxRight.height*2)/2){
                    curIndexLeft.push_back(i);
                    curIndexRight.push_back(a);
                    groupedTargets.push_back(leftCtr[i]);
                    groupedTargets.push_back(rightCtr[a]);
                }
            }
        }
    }
    curIndexLeft.clear();
    curIndexRight.clear();
    leftCtr.clear();
    rightCtr.clear();
    int curClose = 9999;
    int curLeftIndex = 9999;
    int curRightIndex = 9999;

    for(int i = 0; i < groupedTargets.size() - 1; i+= 2){

        std::vector<cv::Point> groupedTarget;
        for(int a = 0; a < groupedTargets[i].size(); a++){
            groupedTarget.push_back(groupedTargets[i][a]);
        }
        for(int a = 0; a < groupedTargets[i+1].size(); a++){
            groupedTarget.push_back(groupedTargets[i+1][a]);
        }
        cv::Rect boundboxLeft = cv::boundingRect(groupedTarget);
        std::cout<<groupedTargets.size()<<std::endl;
        if(abs(boundboxLeft.x - imageCenter) < curClose){
            curLeftIndex = i;
            curRightIndex = i+1;
            curClose = abs(boundboxLeft.x - imageCenter);
        }
    }



    if(curLeftIndex != 9999 && curRightIndex != 9999){
        target.leftTarget = groupedTargets[curLeftIndex];
        target.rightTarget = groupedTargets[curRightIndex];
    }
    else{
        target.leftTarget = std::vector<cv::Point>();
        target.rightTarget =  std::vector<cv::Point>();
    }

    groupedTargets.clear();
    return target;
}
