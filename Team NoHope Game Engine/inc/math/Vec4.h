#pragma once

#ifndef VECTOR4_H
#define VECTOR4_H

namespace NoHope
{
	class Vec4
	{
	public:

		Vec4();
		Vec4(float x, float y, float z, float w);
		~Vec4();
		Vec4(const Vec4& vector);

		float x;
		float y;
		float z;
		float w;

		float magnitude() const;
		void normalize();

		Vec4 operator +(const Vec4& vector) const;
		Vec4 operator -(const Vec4& vector) const;
		Vec4 operator *(const float scalar) const;
		Vec4 operator /(const float scalar) const;
		Vec4& operator =(const Vec4& vector);
		const float& operator [](const unsigned int index) const;

		static Vec4 zero();
	};
}

#endif