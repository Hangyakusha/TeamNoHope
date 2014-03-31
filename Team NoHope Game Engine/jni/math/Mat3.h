#ifndef MAT3_H
#define MAT3_H

#include "math/Vec2.h"
#include "math/Vec3.h"

namespace gg
{
	class Mat3
	{
	public:

		Mat3();
		Mat3(const Vec3& column1, const Vec3& column2, const Vec3& column3);
		Mat3(const float a11, const float a12, const float a13, const float a21, const float a22, const float a23, const float a31, const float a32, const float a33);
		~Mat3();
		Mat3(const Mat3& mat3);

		const float* data();
		static Mat3 identity();
		static Mat3 createRotation(const float rotation);
		static Mat3 createScale(const Vec2& scale);
		static Mat3 createTranslation(const Vec2& scale);

		const Vec3& operator [](unsigned int index) const;
		Mat3 operator *(const Vec3& vector);
		Mat3 operator *(const Mat3& mat3);

	private:

		Vec3 columns[3];
	};
}

#endif