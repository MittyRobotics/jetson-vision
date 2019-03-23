#ifndef VISION_PIPELINEDATA_H
#define VISION_PIPELINEDATA_H

#include <opencv2/core/mat.hpp>
#include "Target.hpp"

struct PipelineData {
	cv::Mat overlayImg;
	Target data;
	bool populated = false;
};

#endif //VISION_PIPELINEDATA_H
