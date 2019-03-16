//
// Created by Owen Leather on 3/14/2019.
//

#ifndef VISION_PIPELINE_H
#define VISION_PIPELINE_H


#include "PipelineData.h"

class Pipeline {
public:
    PipelineData pipeline(cv::Mat img);
};


#endif //VISION_PIPELINE_H
