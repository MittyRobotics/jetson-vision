//
// Created by Owen Leather on 3/14/2019.
//

#include <opencv2/core/mat.hpp>
#include <iostream>
#include "Pipeline.hpp"
#include "Filters.hpp"
#include "Detection.hpp"
#include "Drawing.hpp"
#include "PipelineData.hpp"
#include "Math.hpp"

PipelineData Pipeline::pipeline(cv::Mat img) {
    Filters filters;
    Detection detection;
    Drawing drawing;
    Math math;
    //Filter color

    cv::Mat showImg = img.clone();

    img = filters.filterColor(img);

    //Detect contours

    std::vector<std::vector<cv::Point>> ctr = detection.detectContour(img);
    std::string distanceAndAngle;
    PipelineData data;
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

                        data.overlayImg = showImg;
                        data.data = math.getDistanceAndAngle(target,img.cols/2);
                    }
                }
            }
        }
    }
    if(data.overlayImg.empty() || data.data.empty()){
        data.overlayImg = showImg;
        data.data = std::string("d0a0");
    }
    return (data);
}