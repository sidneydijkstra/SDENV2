
#ifndef TIMER_H
#define TIMER_H

#include <iostream>

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Timer
{
public:
	Timer();
	~Timer();

	// start timer
	void start();
	// get current seconds
	float seconds();
	// stop timer
	void stop();
	// get if timer is running
	bool isRunning();
private:
	bool _running;
	float _offset;
};

#endif /* end TIMER_H */