/**
* @file vector2.h
*
* @brief The Vector2 header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>
#include <string>

/**
* @brief The Vector2 class
*/
class Vector2
{
public:
	///< @brief Constructor of Vector2
	/// @param the x value
	/// @param the y value
	Vector2(float _x, float _y);
	///< @brief Constructor of Vector2
	Vector2();
	~Vector2(); ///< @brief Destructor of Vector2

	float x;
	float y;

	Vector2 normalize();
	float dist(const Vector2& v);
	void limit(const float v);
	
	std::string toString();

	Vector2 zero();

	Vector2 operator+(const Vector2& v);
	Vector2 operator-(const Vector2& v);
	Vector2 operator*(const Vector2& v);

	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	void operator*=(const Vector2& v);

	Vector2 operator+(const float v);
	Vector2 operator-(const float v);
	Vector2 operator*(const float v);

	void operator+=(const float v);
	void operator-=(const float v);
	void operator*=(const float v);

private:
};

#endif /* end VECTOR2_H */