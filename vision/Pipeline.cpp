//
// Created by Owen Leather on 3/14/2019.
//

#include <opencv2/core/mat.hpp>
#include <iostream>
#include "Pipeline.h"
#include "Filters.h"
#include "Detection.h"
#include "Drawing.h"

cv::Mat Pipeline::pipeline(cv::Mat img) {
    Filters filters;
    Detection detection;
    Drawing drawing;
    //Filter color
    cv::Mat showImg = img.clone();
    img = filters.filterColor(img);

    //Detect contours

    std::vector<std::vector<cv::Point>> ctr = detection.detectContour(img);

    //Filter sized
    ctr = filters.filterSize(ctr,0,2000);
    //Detect approx poly
    ctr = detection.getApproxPoly(ctr);
    //Filter verts
    ctr = filters.filterVerts(ctr,4);

    //Detect grouped targets
    Target target = detection.getClosestTarget(ctr, img.cols/2);
    //Draw contours for testing
    ctr.clear();

    ctr.push_back(target.rightTarget);
    ctr.push_back(target.leftTarget);

    img = drawing.drawContours(showImg, ctr);
    return (showImg);
}