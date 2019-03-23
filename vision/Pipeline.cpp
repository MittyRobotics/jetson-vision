#include <opencv2/core/mat.hpp>
#include <iostream>
#include <cv.hpp>
#include "Pipeline.hpp"
#include "Filters.hpp"
#include "Detection.hpp"
#include "Drawing.hpp"
#include "Math.hpp"

Filters filters;
Detection detection;
Drawing drawing;
Math math;

void hsvThreshold(cv::Mat &input, double hue[], double sat[], double val[], cv::Mat &out) {
	cv::cvtColor(input, out, cv::COLOR_BGR2HSV);
	cv::inRange(out, cv::Scalar(hue[0], sat[0], val[0]), cv::Scalar(hue[1], sat[1], val[1]), out);
}

void findContours(cv::Mat &input, bool externalOnly, std::vector<std::vector<cv::Point> > &contours) {
	std::vector<cv::Vec4i> hierarchy;
	contours.clear();
	int mode = externalOnly ? cv::RETR_EXTERNAL : cv::RETR_LIST;
	int method = cv::CHAIN_APPROX_SIMPLE;
	cv::findContours(input, contours, hierarchy, mode, method);
}

/**
 * Filters through contours.
 * @param inputContours is the input vector of contours.
 * @param minArea is the minimum area of a contour that will be kept.
 * @param minPerimeter is the minimum perimeter of a contour that will be kept.
 * @param minWidth minimum width of a contour.
 * @param maxWidth maximum width.
 * @param minHeight minimum height.
 * @param maxHeight  maximimum height.
 * @param solidity the minimum and maximum solidity of a contour.
 * @param minVertexCount minimum vertex Count of the contours.
 * @param maxVertexCount maximum vertex Count.
 * @param minRatio minimum ratio of width to height.
 * @param maxRatio maximum ratio of width to height.
 * @param output vector of filtered contours.
 */
void filterContours(std::vector<std::vector<cv::Point> > &inputContours, double minArea, double minPerimeter,
                    double minWidth, double maxWidth, double minHeight, double maxHeight, double solidity[],
                    double maxVertexCount, double minVertexCount, double minRatio, double maxRatio,
                    std::vector<std::vector<cv::Point> > &output) {
	std::vector<cv::Point> hull;
	output.clear();
	for (const std::vector<cv::Point> &contour: inputContours) {
		cv::Rect bb = boundingRect(contour);
		//if (bb.width < minWidth || bb.width > maxWidth) continue;
		if (bb.height < minHeight || bb.height > maxHeight) continue;
		//double area = cv::contourArea(contour);
		//if (area < minArea) continue;
		//if (arcLength(contour, true) < minPerimeter) continue;
		//cv::convexHull(cv::Mat(contour, true), hull);
		//double solid = 100 * area / cv::contourArea(hull);
		//if (solid < solidity[0] || solid > solidity[1]) continue;
		//if (contour.size() < minVertexCount || contour.size() > maxVertexCount)	continue;
		//double ratio = (double) bb.width / (double) bb.height;
		//if (ratio < minRatio || ratio > maxRatio) continue;
		output.push_back(contour);
	}
}

PipelineData Pipeline::pipeline(cv::Mat img) {
	cv::Mat tmp = img.clone();
	std::vector<std::vector<cv::Point> > ctrs1;
	std::vector<std::vector<cv::Point> > ctrs2;



	//s("Original", img.clone());


	double hsvThresholdHue[] = {0.0, 180.0};
	double hsvThresholdSaturation[] = {0.0, 255.0};
	double hsvThresholdValue[] = {128.41726618705036, 255.0};
	hsvThreshold(img, hsvThresholdHue, hsvThresholdSaturation, hsvThresholdValue, img);

	//s("Green", img.clone());


	bool findContoursExternalOnly = false;  // default Boolean
	findContours(img, findContoursExternalOnly, ctrs1);

	/*cv::Mat tmp1 = tmp.clone();
	for (int i = 0; i < ctrs1.size(); i++)
		cv::drawContours(tmp1, ctrs1, i, cv::Scalar(0, 0, 255));
	s("ctrs", tmp1);*/


	if (!ctrs1.empty()) {
		double filterContoursMinArea = 0.0;  // default Double
		double filterContoursMinPerimeter = 0;  // default Double
		double filterContoursMinWidth = 0;  // default Double
		double filterContoursMaxWidth = 1000;  // default Double
		double filterContoursMinHeight = 0;  // default Double
		double filterContoursMaxHeight = 2000;  // default Double
		double filterContoursSolidity[] = {0, 100};
		double filterContoursMaxVertices = 1000000;  // default Double
		double filterContoursMinVertices = 0;  // default Double
		double filterContoursMinRatio = 0;  // default Double
		double filterContoursMaxRatio = 1000.0;  // default Double
		filterContours(ctrs1, filterContoursMinArea, filterContoursMinPerimeter, filterContoursMinWidth,
		               filterContoursMaxWidth, filterContoursMinHeight, filterContoursMaxHeight, filterContoursSolidity,
		               filterContoursMaxVertices, filterContoursMinVertices, filterContoursMinRatio,
		               filterContoursMaxRatio,
		               ctrs2);

		std::cout << ctrs2.size() << std::endl;

		cv::Mat tmp1 = tmp.clone();
		for (int i = 0; i < ctrs2.size(); i++)
			cv::drawContours(tmp1, ctrs2, i, cv::Scalar(0, 0, 255));
		s("ctrs2", tmp1);


		if (!ctrs2.empty()) {
			ctrs1.clear();
			for (const auto &ctr : ctrs2) {
				std::vector<cv::Point> approxPoly;
				cv::approxPolyDP(ctr, approxPoly, 0.04 * arcLength(ctr, true), true);
				ctrs1.push_back(approxPoly);
			}

			tmp1 = tmp.clone();
			for (int i = 0; i < ctrs1.size(); i++)
				cv::drawContours(tmp1, ctrs1, i, cv::Scalar(0, 0, 255));
			s("ctrs1", tmp1);


			if (!ctrs1.empty()) {
				ctrs2.clear();
				for (auto &ctr : ctrs1) {
					if (ctr.size() == 4) {
						ctrs2.push_back(ctr);
					}
				}


				if (!ctrs2.empty()) {
					std::vector<std::vector<cv::Point>> leftCtrs;
					std::vector<std::vector<cv::Point>> rightCtrs;
					for (const auto &ctr : ctrs2) {
						if (cv::minAreaRect(ctr).angle < 90) {
							leftCtrs.push_back(ctr);
						} else {
							rightCtrs.push_back(ctr);
						}
					}


					std::vector<Target> groupedTargets;
					for (const auto &leftCtr : leftCtrs) {
						for (const auto &rightCtr : rightCtrs) {
							cv::Rect left = cv::boundingRect(leftCtr);
							cv::Rect right = cv::boundingRect(rightCtr);
							if (left.x < right.x) {
								if (abs(left.x - right.x) < (left.height * 2.5 + right.height * 2.5) / 2) {
									groupedTargets.push_back(Target{leftCtr, rightCtr});
								}
							}
						}
					}


					if (!groupedTargets.empty()) {
						Target target;
						double angleDifference = 1337;
						for (const auto &groupedTarget : groupedTargets) {
							double angle = cachedAngle - abs(groupedTarget.getAngle());
							if (angle < angleDifference) {
								target = groupedTarget;
								angleDifference = angle;
							}
						}


						// TODO Rest of Pipeline
					}
				}
			}
		}
	}


	PipelineData data;



	/*

				//Detect grouped targets
				Target target = detection.getClosestTarget(ctr, img.cols / 2);
				if(target.leftTarget.size() > 1 && target.rightTarget.size() > 1){
					//Clear contour
					ctr.clear();

					//Add left and right target to contour for drawing
					ctr.push_back(target.rightTarget);
					ctr.push_back(target.leftTarget);

					//Draw target contours on overlay image
					img = drawing.drawContours(showImg, ctr);

					data.overlayImg = img;
					data.data = math.getDistanceAndAngle(target,img.cols/2);
				}
			}
		}
	}
}
	  */
	if (data.overlayImg.empty() || data.data.empty()) {
		data.overlayImg = img;
		data.data = std::string("d0a0");
	}
	return (data);
}

void Pipeline::s(const char *name, const cv::Mat mat) {
	cv::imshow(name, mat);
	cv::waitKey(1);
}