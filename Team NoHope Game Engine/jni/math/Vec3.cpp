#include "Vec3.h"
#include <cmath>

using namespace gg;

Vec3::Vec3():
	x(0),
	y(0),
	z(0)
{}

Vec3::~Vec3() {}

Vec3::Vec3(float x, float y, float z):
	x(x),
	y(y),
	z(z)
{}

Vec3::Vec3(const Vec3& vector):
	x(vector.x),
	y(vector.y),
	z(vector.z)
{}

float Vec3::magnitude() const
{
	return (sqrt(x*x + y*y + z*z));
}

void Vec3::normalize()
{
	*this = *this / magnitude();
}

Vec3 Vec3::operator +(const Vec3& vector) const
{
	return Vec3(x + vector.x, y + vector.y, z + vector.z);
}

Vec3 Vec3::operator +(const Vec2& vector) const
{
	return Vec3(x + vector.x, y + vector.y, z);
}

Vec3 Vec3::operator -(const Vec3& vector) const
{
	return Vec3(x - vector.x, y - vector.y, z - vector.z);
}

Vec3 Vec3::operator *(const float scalar) const
{
	return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator /(const float scalar) const
{
	return Vec3(x / scalar, y / scalar, z / scalar);
}

Vec3& Vec3::operator =(const Vec3& vector)
{
	if(this != &vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
	}

	return *this;
}

const float& Vec3::operator [](const unsigned int index) const
{
	return (&x)[index];
}

Vec3 Vec3::zero()
{
	return Vec3();
}