#include "ProcessThread.hpp"

bool ProcessThread::function() {
	if (taskPending) {
		taskPending = false;
		selectingThread.data = pipeline.pipeline(frame);
		if (!selectingThread.data.populated) {
			selectingThread.data.data.setDistance(0.0);
		}
		selectingThread.taskPending = true;
	}
	return true;
}
