#include "SocketThread.hpp"

bool SocketThread::function() {
	if (taskPending) {
		socket.sendData(data.data);
		taskPending = false;
	}
	return true;
}
