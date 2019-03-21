#include "ProcessThread.hpp"

bool ProcessThread::function() {
	if (taskPending) {
		taskPending = false;
		socketThread.data = pipeline.pipeline(frame);
		socketThread.taskPending = true;
	}
	return true;
}
