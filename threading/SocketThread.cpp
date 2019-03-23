#include "SocketThread.hpp"

bool SocketThread::function() {
	if (taskPending) {
		taskPending = false;
		return socket.sendData(data.data);
	}
	return true;
}
