#include "timer.h"

Timer::Timer(){
	_running = false;
	_offset = 0.0f;
}

Timer::~Timer(){
}

void Timer::start(){
	_offset = glfwGetTime();
	_running = true;
}

float Timer::seconds(){
	if(_running)
		return glfwGetTime() - _offset;
	return 0.0f;
}

void Timer::stop(){
	_running = false;
}

bool Timer::isRunning(){
	return _running;
}
