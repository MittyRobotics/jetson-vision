#ifndef VISION_PROCESSTHREAD_HPP
#define VISION_PROCESSTHREAD_HPP

#include <opencv2/core/mat.hpp>
#include "Thread.hpp"
#include "../vision/Pipeline.hpp"
#include "SocketThread.hpp"

class ProcessThread : public Thread {
public:
	ProcessThread() = default;

public:
	bool function() override;

public:
	bool taskPending = false;

	cv::Mat frame;

private:
	Pipeline pipeline;

private:
	SocketThread socketThread;
};

#endif //VISION_PROCESSTHREAD_HPP
