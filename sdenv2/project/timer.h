/**
* @file timer.h
*
* @brief The Timer header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef TIMER_H
#define TIMER_H

#include <iostream>

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
* @brief The Timer class
*/
class Timer
{
public:
	Timer(); ///< @brief Constructor of the Timer
	~Timer(); ///< @brief Destructor of the Timer

	/// @brief start the Timer
	/// @return void
	void start();
	/// @brief get the amount of seconds
	/// @return float
	float seconds();
	/// @brief stop the Timer
	/// @return void
	void stop();
	/// @brief get if the Timer is running
	/// @return bool
	bool isRunning();
private:
	bool _running; ///< @brief the running bool
	float _offset; ///< @brief the offset for the time
};

#endif /* end TIMER_H */