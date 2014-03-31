#ifndef VECTOR2_H
#define VECTOR2_H

namespace gg
{
	class Vec2
	{
	public:

		Vec2();
		Vec2(float x, float y);
		~Vec2();
		Vec2(const Vec2& vector);

		float x;
		float y;

		float magnitude() const;
		void normalize();

		Vec2 operator +(const Vec2& vector) const;
		Vec2 operator -(const Vec2& vector) const;
		Vec2 operator *(const float scalar) const;
		Vec2 operator /(const float scalar) const;
		Vec2& operator =(const Vec2& vector);

		static Vec2 zero();
	};
}

#endif