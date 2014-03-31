#include "Vec4.h"
#include <cmath>

using namespace gg;

Vec4::Vec4():
	x(0),
	y(0),
	z(0),
	w(0)
{}

Vec4::~Vec4() {}

Vec4::Vec4(float x, float y, float z, float w):
	x(x),
	y(y),
	z(z),
	w(w)
{}

Vec4::Vec4(const Vec4& vector):
	x(vector.x),
	y(vector.y),
	z(vector.z),
	w(vector.w)
{}

float Vec4::magnitude() const
{
	return (sqrt(x*x + y*y + z*z + w*w));
}

void Vec4::normalize()
{
	*this = *this / magnitude();
}

Vec4 Vec4::operator +(const Vec4& vector) const
{
	return Vec4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
}

Vec4 Vec4::operator -(const Vec4& vector) const
{
	return Vec4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
}

Vec4 Vec4::operator *(const float scalar) const
{
	return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

Vec4 Vec4::operator /(const float scalar) const
{
	return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
}

Vec4& Vec4::operator =(const Vec4& vector)
{
	if(this != &vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
		w = vector.w;
	}

	return *this;
}

const float& Vec4::operator [](const unsigned int index) const
{
	return (&x)[index];
}

Vec4 Vec4::zero()
{
	return Vec4();
}