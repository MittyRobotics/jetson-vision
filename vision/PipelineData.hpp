//
// Created by Owen Leather on 3/16/2019.
//

#ifndef VISION_PIPELINEDATA_H
#define VISION_PIPELINEDATA_H

#include <opencv2/core/mat.hpp>

class PipelineData{
public:
    cv::Mat overlayImg;
    std::string data;
};

#endif //VISION_PIPELINEDATA_H