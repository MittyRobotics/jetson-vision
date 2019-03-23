#include "Thread.hpp"

Thread::Thread() = default;

Thread::~Thread() {
	running = false;
	thread.join();
}

void Thread::threadFunction() {
	while (running && function()) {}
}
