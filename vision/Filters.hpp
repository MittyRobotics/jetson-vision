#ifndef VISION_FILTERS_H
#define VISION_FILTERS_H


class Filters {
public:
	void filterColor(cv::Mat img);

public:
	std::vector<std::vector<cv::Point>>
	filterSize(std::vector<std::vector<cv::Point>> ctr, int minHeight, int maxHeight);

public:
	std::vector<std::vector<cv::Point>> filterVerts(std::vector<std::vector<cv::Point>> ctr, int vertCount);
};


#endif //VISION_FILTERS_H
