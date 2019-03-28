#include "ProcessThread.hpp"

bool ProcessThread::function() {
	if (taskPending) {
		while (selectingThread.taskPending) {}
		selectingThread.data = pipeline.pipeline(frame);
		selectingThread.taskPending = true;
		taskPending = false;
	}
	return true;
}
