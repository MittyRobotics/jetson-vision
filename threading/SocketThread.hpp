#ifndef VISION_SOCKETTHREAD_HPP
#define VISION_SOCKETTHREAD_HPP

#include "Thread.hpp"
#include "../vision/PipelineData.hpp"
#include "../sockets/SocketConnection.hpp"

class SocketThread : public Thread {
public:
	SocketThread() = default;

public:
	bool function() override;

public:
	bool taskPending = false;

	PipelineData data;

private:
	SocketConnection socket;
};

#endif //VISION_SOCKETTHREAD_HPP
