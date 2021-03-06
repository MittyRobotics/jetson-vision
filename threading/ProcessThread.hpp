#ifndef VISION_PROCESSTHREAD_HPP
#define VISION_PROCESSTHREAD_HPP

#include <opencv2/core/mat.hpp>
#include "Thread.hpp"
#include "../vision/Pipeline.hpp"
#include "SocketThread.hpp"
#include "SelectingThread.hpp"

class ProcessThread : public Thread {
public:
	ProcessThread() = default;

public:
	bool function() override;

public:
	bool taskPending = false;

	cv::Mat frame;

private:
	Pipeline pipeline = Pipeline();

private:
	SelectingThread selectingThread;
};

#endif //VISION_PROCESSTHREAD_HPP
