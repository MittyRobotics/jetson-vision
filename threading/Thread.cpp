#include "Thread.hpp"

#include <iostream>

Thread::Thread() = default;

Thread::~Thread() {
	running = false;
	thread.join();
}

void Thread::threadFunction() {
	while (running && function()) {}
}
