/**
* @file color.h
*
* @brief The Color header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
* @brief The Color class
*/
class Color
{
public:
	///< @brief Constructor of the Color
	/// @param the red compoment
	/// @param the green compoment
	/// @param the blue compoment
	Color(int _r = 0, int _g = 0, int _b = 0);
	~Color(); ///< @brief Destructor of the Color

	/// @brief set the color
	/// @param the red compoment
	/// @param the green compoment
	/// @param the blue compoment
	/// @return void
	void setColor(int _r, int _g, int _b);
	/// @brief set the color
	/// @param the red green and blue compoment in a glm::vec3
	/// @return void
	void setColor(glm::vec3 _c);

	/// @brief get the color in the glsl format
	/// @return glm::vec3
	glm::vec3 getColor();

	/// @brief lerp the color
	/// @param the starting lerp color
	/// @param the ending lerp color
	/// @param the lerp amount
	/// @return Color
	Color lerpColor(Color c1, Color c2, float amount);

	short int r; ///< @brief the red compoment of the color
	short int g; ///< @brief the green compoment of the color
	short int b; ///< @brief the blue compoment of the color
private:

};

#endif /* end COLOR_H */