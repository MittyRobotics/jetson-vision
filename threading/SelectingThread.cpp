#include "SelectingThread.hpp"

bool SelectingThread::function() {
	if (taskPending) {
		taskPending = false;
		if (data.data.getDistance() > 50) {
			calculateOffsetTarget();
		}
		socketThread.data = data;
		socketThread.taskPending = true;
	}
	return true;
}

void SelectingThread::calculateOffsetTarget() {
	data.data.setAngle(data.data.getAngle() * 1.1);
}