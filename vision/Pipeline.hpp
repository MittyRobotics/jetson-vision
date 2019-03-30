#ifndef VISION_PIPELINE_H
#define VISION_PIPELINE_H

#include "PipelineData.hpp"
#include "Target.hpp"

class Pipeline {
public:
	Pipeline() = default;

public:
	PipelineData pipeline(cv::Mat img) const;

	void s(const char *name, cv::Mat mat) const;

private:
	double cachedAngle;
};


#endif //VISION_PIPELINE_H
