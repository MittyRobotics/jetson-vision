#include "pch.h"
#include "Pipeline.h"


cv::Mat pipeline(cv::Mat img) {
	//Filter color
	cv::Mat showImg = img.clone();
	img = filterColor(img);
	
	//Detect contours
	std::vector<std::vector<cv::Point>> ctr = detectContour(img);

	//Filter sized
	ctr = filterSize(ctr,0,200);

	//Detect approx poly
	std::vector<cv::Point> approxPoly;
	approxPoly = getApproxPoly(ctr);
	//Draw contours for testing
	img = drawContours(showImg, ctr);

	//Filter verts

	//Detect left and right

	//Group targets

	return (showImg);
}