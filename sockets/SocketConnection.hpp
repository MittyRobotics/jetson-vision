#ifndef VISION_SOCKETCONNECTION_HPP
#define VISION_SOCKETCONNECTION_HPP

#include <string>

class SocketConnection {
public:
	SocketConnection();

	~SocketConnection();

public:
	void sendDistance(double distance);
	void sendAngle(double angle);

private:
	void send(const char *string);
};

#endif //VISION_SOCKETCONNECTION_HPP
