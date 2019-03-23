#include "ProcessThread.hpp"

bool ProcessThread::function() {
	if (taskPending) {
		taskPending = false;
		socketThread.data = pipeline.pipeline(frame);
		if (socketThread.data.populated) {
			socketThread.taskPending = true;
		}
	}
	return true;
}
