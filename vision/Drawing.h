#ifndef VISION_DRAWING_H
#define VISION_DRAWING_H


class Drawing{
public:
    cv::Mat drawContours(cv::Mat img, std::vector<std::vector<cv::Point>> ctr);
};

#endif //VISION_DRAWING_H
