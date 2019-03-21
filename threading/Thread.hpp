#ifndef VISION_THREAD_HPP
#define VISION_THREAD_HPP

#include <thread>

class Thread {
public:
	Thread();

	~Thread();


protected:
	std::thread thread = std::thread(&Thread::threadFunction, this);

	virtual bool function() = 0;


public:
	void threadFunction();

	bool running = true;
};

#endif //VISION_THREAD_HPP
