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

    if(ctr.size() > 1){
        //Filter sized

        ctr = filters.filterSize(ctr,0,2000);
        if(ctr.size() > 1) {
            std::cout << "test" << std::endl;
            //Detect approx poly
            ctr = detection.getApproxPoly(ctr);
            if(ctr.size() > 1) {
                //Filter verts
                ctr = filters.filterVerts(ctr, 4);
                if(ctr.size() > 1) {
                    //Detect grouped targets
                    Target target = detection.getClosestTarget(ctr, img.cols / 2);
                    if(target.leftTarget.size() > 1 && target.rightTarget.size() > 1){
                        //Clear contour
                        ctr.clear();

                        //Add left and right target to contour for drawing
                        ctr.push_back(target.rightTarget);
                        ctr.push_back(target.leftTarget);

                        //Draw target contours on overlay image
                        showImg = drawing.drawContours(showImg, ctr);
                    }
                }
            }
        }
    }

    return (showImg);
}