#include "vector2.h"

Vector2::Vector2(float _x, float _y){
	this->x = _x;
	this->y = _y;
}

Vector2::Vector2()
{
}

Vector2::~Vector2(){
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2 Vector2::normalize(){
	Vector2 n = Vector2(0, 0);

	n.x = 1 / this->x;
	n.y = 1 / this->y;

	return n;
}

float Vector2::dist(const Vector2 & v){
	return sqrt(pow(v.x - this->x, 2) + pow(v.y - this->y, 2));
}

void Vector2::limit(const float v){ // (state > ment) ? true : false
	this->x = (x > v) ? v : (x < -v) ? -v : x;
	this->y = (y > v) ? v : (y < -v) ? -v : y;
}

std::string Vector2::toString(){
	return "x: " + std::to_string(x) + " y: " + std::to_string(y);
}

Vector2 Vector2::zero()
{
	return Vector2(0,0);
}

Vector2 Vector2::operator+(const Vector2 & v){
	Vector2 n = Vector2(0,0);

	n.x = this->x + v.x;
	n.y = this->y + v.y;

	return n;
}

Vector2 Vector2::operator-(const Vector2 & v){
	Vector2 n = Vector2(0, 0);

	n.x = this->x - v.x;
	n.y = this->y - v.y;

	return n;
}

Vector2 Vector2::operator*(const Vector2 & v){
	Vector2 n = Vector2(0, 0);

	n.x = this->x * v.x;
	n.y = this->y * v.y;

	return n;
}

void Vector2::operator+=(const Vector2 & v){
	this->x = this->x + v.x;
	this->y = this->y + v.y;
}

void Vector2::operator-=(const Vector2 & v){
	this->x = this->x - v.x;
	this->y = this->y - v.y;
}

void Vector2::operator*=(const Vector2 & v){
	this->x = this->x * v.x;
	this->y = this->y * v.y;
}

Vector2 Vector2::operator+(const float v){
	Vector2 n = Vector2(0, 0);

	n.x = this->x + v;
	n.y = this->y + v;

	return n;
}

Vector2 Vector2::operator-(const float v){
	Vector2 n = Vector2(0, 0);

	n.x = this->x - v;
	n.y = this->y - v;

	return n;
}

Vector2 Vector2::operator*(const float v){
	Vector2 n = Vector2(0, 0);

	n.x = this->x * v;
	n.y = this->y * v;

	return n;
}

void Vector2::operator+=(const float v){
	this->x = this->x + v;
	this->y = this->y + v;
}

void Vector2::operator-=(const float v){
	this->x = this->x - v;
	this->y = this->y - v;
}

void Vector2::operator*=(const float v){
	this->x = this->x * v;
	this->y = this->y * v;
}
