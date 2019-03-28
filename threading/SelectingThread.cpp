#include "SelectingThread.hpp"

bool SelectingThread::function() {
	if (taskPending) {
		if (!data.populated) {
			data.data.setDistance(0.0);
		}
		while (socketThread.taskPending) {}
		socketThread.data = data;
		socketThread.taskPending = true;
		taskPending = false;
	}
	return true;
}

void SelectingThread::calculateOffsetTarget() {
	data.data.setAngle(data.data.getAngle() * 1.2);
}
