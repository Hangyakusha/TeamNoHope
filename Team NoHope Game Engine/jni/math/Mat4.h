#ifndef MAT4_H
#define MAT4_H

#include <math/Vec3.h>
#include <math/Vec4.h>

namespace gg
{
	class Mat4
	{
	public:

		Mat4();
		Mat4(const Vec4& column1, const Vec4& column2, const Vec4& column3, const Vec4& column4);
		Mat4(const float a11, const float a12, const float a13, const float a14,
			const float a21, const float a22, const float a23, const float a24,
			const float a31, const float a32, const float a33, const float a34,
			const float a41, const float a42, const float a43, const float a44);
		~Mat4();
		Mat4(const Mat4& mat4);

		const float* data();
		static Mat4 identity();
		static Mat4 createRotationX(const float rotation);
		static Mat4 createRotationY(const float rotation);
		static Mat4 createRotationZ(const float rotation);
		static Mat4 createScale(const Vec3& scale);
		static Mat4 createScale(const float scale);
		static Mat4 createTranslation(const Vec3& translation);

		const Vec4& operator [](unsigned int index) const;
		Mat4 operator *(const Vec4& vector);
		Mat4 operator *(const Mat4& mat4);

	private:

		Vec4 columns[4];

	};
}

#endif