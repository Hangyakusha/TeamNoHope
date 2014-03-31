#include "Vec2.h"
#include <cmath>

using namespace gg;

Vec2::Vec2():
	x(0),
	y(0)
{}

Vec2::~Vec2() {}

Vec2::Vec2(float x, float y):
	x(x),
	y(y)
{}

Vec2::Vec2(const Vec2& vector):
	x(vector.x),
	y(vector.y)
{}

float Vec2::magnitude() const
{
	return sqrt(x * x + y * y);
}

void Vec2::normalize()
{
	*this = *this / magnitude();
}

Vec2 Vec2::operator +(const Vec2& vector) const
{
	return Vec2(x + vector.x, y + vector.y);
}

Vec2 Vec2::operator -(const Vec2& vector) const
{
	return Vec2(x - vector.x, y - vector.y);
}

Vec2 Vec2::operator *(const float scalar) const
{
	return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator /(const float scalar) const
{
	return Vec2(x / scalar, y / scalar);
}

Vec2& Vec2::operator =(const Vec2& vector)
{
	if(this != &vector)
	{
		x = vector.x;
		y = vector.y;
	}

	return *this;
}

Vec2 Vec2::zero()
{
	return Vec2();
}