#ifndef VISION_SOCKETCONNECTION_HPP
#define VISION_SOCKETCONNECTION_HPP

#include <string>
#include "../vision/PipelineData.hpp"

class SocketConnection {
public:
	SocketConnection();

	~SocketConnection();

public:
	bool sendData(Target data) const;

private:
	bool send(const char *string) const;
};

#endif //VISION_SOCKETCONNECTION_HPP
