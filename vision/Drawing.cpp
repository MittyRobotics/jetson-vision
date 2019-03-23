#include <opencv2/imgproc.hpp>
#include "Drawing.hpp"

cv::Mat Drawing::drawContours(cv::Mat img, std::vector<std::vector<cv::Point>> ctr) {
	for (int i = 0; i < ctr.size(); i++) {
		cv::drawContours(img, ctr, i, cv::Scalar(255, 0, 0));
	}
	return img;
}
