/**
* @file spriteanimator.h
*
* @brief The SpriteAnimator header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef SPRITEANIMATOR_H
#define SPRITEANIMATOR_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// include sprite
#include "sprite.h"

/**
* @brief The Animation struct
*/
struct Animation{
	const char* id; ///< @brief the location of the texture
	float delay; ///< @brief the delay between texture switch
};

/**
* @brief The SpriteAnimator struct
*/
class SpriteAnimator
{
public:
	SpriteAnimator(); ///< @brief Constructor of the SpriteAnimator
	virtual ~SpriteAnimator(); ///< @brief Destructor of the SpriteAnimator

	/// @brief the update function of the SpriteAnimator
	/// @return void
	void update();

	/// @brief add the animations
	/// @param the animations locations
	/// @param the delay between animations
	/// @param the filter type
	/// @param the wrap type
	/// @return void
	void setAnimations(std::vector<const char*> locations, float delay, int filter, int wrap);
	/// @brief get the current animation
	/// @return const char*
	const char* getCurrentAnimation() { return _animations[_currentAnimation].id; };

	/// @brief get the filter type
	/// @return int
	int filter() { return _filter; }
	/// @brief get the wrap type
	/// @return int
	int wraping() { return _wrap; }

private:
	std::vector<Animation> _animations; ///< @brief the list of animations
	int _currentAnimation; ///< @brief the current animation
	float _timer; ///< @brief the timer

	int _filter; ///< @brief the filter type
	int _wrap; ///< @brief the wrap type
}; 

#endif /* end SPRITEANIMATOR_H */
