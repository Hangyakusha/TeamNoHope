#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vec2.h"

namespace NoHope
{
	class Vec3
	{
	public:

		Vec3();
		Vec3(float x, float y, float z);
		~Vec3();
		Vec3(const Vec3& vector);

		float x;
		float y;
		float z;

		float magnitude() const;
		void normalize();

		Vec3 operator +(const Vec3& vector) const;
		Vec3 operator +(const Vec2& vector) const;
		Vec3 operator -(const Vec3& vector) const;
		Vec3 operator *(const float scalar) const;
		Vec3 operator /(const float scalar) const;
		Vec3& operator =(const Vec3& vector);
		const float& operator [](const unsigned int index) const;

		static Vec3 zero();
	};
}

#endif