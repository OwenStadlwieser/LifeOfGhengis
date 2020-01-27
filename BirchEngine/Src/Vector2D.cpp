#include "Vector2D.h"
#include <iostream>
Vector2D::Vector2D()
{
	y = 0.0f;
	x = 0.0f;
}
Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector2D& Vector2D::Add(const Vector2D& vec) 
{
	std::cout << vec << std::endl;
	this->x = x + vec.x;
	this->y = y + vec.y;
	return *this;
}
Vector2D& Vector2D::Sub(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
Vector2D& Vector2D::Mult(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}
Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}
Vector2D& operator+ (Vector2D& v1, const Vector2D& v2) {
	return v1.Add(v2);
}
Vector2D& operator- (Vector2D& v1, const Vector2D& v2) {
	return v1.Sub(v2);
}
Vector2D& operator* (Vector2D& v1, const Vector2D& v2) {
	return v1.Mult(v2);
}
Vector2D& operator/ (Vector2D& v1, const Vector2D& v2) {
	return v1.Divide(v2);
}
Vector2D& Vector2D::operator+=(const Vector2D& v2)
{
	return this->Add(v2);
}
Vector2D& Vector2D::operator-=(const Vector2D& v2)
{
	return this->Sub(v2);
}
Vector2D& Vector2D::operator*=(const Vector2D& v2)
{
	return this->Mult(v2);
}
Vector2D& Vector2D::operator/=(const Vector2D& v2)
{
	return this->Divide(v2);
}
Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;
	return *this;
}
Vector2D& Vector2D::Zero()
{
	this->y = 0;
	this->x = 0;
	return *this;
}
std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}
