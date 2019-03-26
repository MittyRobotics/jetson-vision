#ifndef VISION_SELECTINGTHREAD_HPP
#define VISION_SELECTINGTHREAD_HPP

#include "Thread.hpp"
#include "../vision/PipelineData.hpp"
#include "../sockets/SocketConnection.hpp"
#include "SocketThread.hpp"

class SelectingThread : public Thread {
public:
	SelectingThread() = default;

public:
	bool function() override;

public:
	bool taskPending = false;

	PipelineData data;

private:
	void calculateOffsetTarget();

private:
	SocketThread socketThread;
};


#endif //VISION_SELECTINGTHREAD_HPP
