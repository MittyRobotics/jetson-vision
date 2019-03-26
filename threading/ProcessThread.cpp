#include "ProcessThread.hpp"

bool ProcessThread::function() {
	if (taskPending) {
		taskPending = false;
		selectingThread.data = pipeline.pipeline(frame);
		if (selectingThread.data.populated) {
			selectingThread.taskPending = true;
		}
	}
	return true;
}
