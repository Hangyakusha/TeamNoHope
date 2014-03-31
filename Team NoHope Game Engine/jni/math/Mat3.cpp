#include "Mat3.h"
#include <math.h>

using namespace gg;

Mat3::Mat3()
{
	*this = identity();
}

Mat3::Mat3(const Vec3& column1, const Vec3& column2, const Vec3& column3)
{
	columns[0] = column1;
	columns[1] = column2;
	columns[2] = column3;
}

Mat3::Mat3(const float a11, const float a12, const float a13, const float a21, const float a22, const float a23, const float a31, const float a32, const float a33)
{
	columns[0] = Vec3(a11, a12, a13);
	columns[1] = Vec3(a21, a22, a23);
	columns[2] = Vec3(a31, a32, a33);
}

Mat3::Mat3(const Mat3& mat3)
{
	columns[0] = mat3[0];
	columns[1] = mat3[1];
	columns[2] = mat3[2];
}

Mat3::~Mat3() {}

Mat3 Mat3::identity()
{
	return Mat3(1, 0, 0,
				0, 1, 0,
				0, 0, 1);
}

Mat3 Mat3::createRotation(const float rotation)
{
	return Mat3(	cos(rotation),	sin(rotation),	0,
					-sin(rotation),	cos(rotation),	0,
					0,				0,				1.0f	);
}

Mat3 Mat3::createScale(const Vec2& scale)
{
	return Mat3(	scale.x,	0,			0,
					0,			scale.y,	0,
					0,			0,			1.0f	);
}

Mat3 Mat3::createTranslation(const Vec2& translation)
{
	return Mat3(	1.0f,			0,				0,
					0,				1.0f,			0,
					translation.x,	translation.y,	1.0f	);
}

const float* Mat3::data()
{
	return &columns[0].x;
}

const Vec3& Mat3::operator [](const unsigned int index) const
{
	return columns[index];
}

Mat3 Mat3::operator *(const Mat3& mat3)
{
	return Mat3(	mat3[0][0] * columns[0][0] + mat3[0][1] * columns[1][0] + mat3[0][2] * columns[2][0],
					mat3[0][0] * columns[0][1] + mat3[0][1] * columns[1][1] + mat3[0][2] * columns[2][1],
					mat3[0][0] * columns[0][2] + mat3[0][1] * columns[1][2] + mat3[0][2] * columns[2][2],

					mat3[1][0] * columns[0][0] + mat3[1][1] * columns[1][0] + mat3[1][2] * columns[2][0],
					mat3[1][0] * columns[0][1] + mat3[1][1] * columns[1][1] + mat3[1][2] * columns[2][1],
					mat3[1][0] * columns[0][2] + mat3[1][1] * columns[1][2] + mat3[1][2] * columns[2][2],

					mat3[2][0] * columns[0][0] + mat3[2][1] * columns[1][0] + mat3[2][2] * columns[2][0],
					mat3[2][0] * columns[0][1] + mat3[2][1] * columns[1][1] + mat3[2][2] * columns[2][1],
					mat3[2][0] * columns[0][2] + mat3[2][1] * columns[1][2] + mat3[2][2] * columns[2][2]
				);
}