#include "math/Mat4.h"
#include <math.h>

using namespace NoHope;

Mat4::Mat4()
{
	*this = identity();
}

Mat4::Mat4(const Vec4& column1, const Vec4& column2, const Vec4& column3, const Vec4& column4)
{
	columns[0] = column1;
	columns[1] = column2;
	columns[2] = column3;
	columns[3] = column4;
}

Mat4::Mat4(const float a11, const float a12, const float a13, const float a14,
			const float a21, const float a22, const float a23, const float a24,
			const float a31, const float a32, const float a33, const float a34,
			const float a41, const float a42, const float a43, const float a44)
{
	columns[0] = Vec4(a11, a12, a13, a14);
	columns[1] = Vec4(a21, a22, a23, a24);
	columns[2] = Vec4(a31, a32, a33, a34);
	columns[3] = Vec4(a41, a42, a43, a44);
}

Mat4::Mat4(const Mat4& Mat4)
{
	columns[0] = Mat4[0];
	columns[1] = Mat4[1];
	columns[2] = Mat4[2];
	columns[3] = Mat4[3];
}

Mat4::~Mat4() {}

Mat4 Mat4::identity()
{
	return Mat4(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
}

Mat4 Mat4::createRotationX(const float rotation)
{
	return Mat4(    1.0f,		0,					0,				0,
					0,		cos(rotation),		sin(rotation),	0,
					0,		-sin(rotation),		cos(rotation),	0,
					0,		0,					0,				1.0f);
}

Mat4 Mat4::createRotationY(const float rotation)
{
	return Mat4(    cos(rotation),		0,				sin(rotation),		0,
					0,					1.0f,				0,					0,
					-sin(rotation),		0,				cos(rotation),		0,
					0,					0,				0,					1.0f);
}

Mat4 Mat4::createRotationZ(const float rotation)
{
	return Mat4(	cos(rotation),		-sin(rotation),		0,		0,
					sin(rotation),		cos(rotation),		0,		0,
					0,					0,					1.0f,	0,
					0,					0,					0,		1.0f);
}

Mat4 Mat4::createScale(const Vec3& scale)
{
	return Mat4(	scale.x,	0,			0,			0,
					0,			scale.y,	0,			0,
					0,			0,			scale.z,	0,
					0,			0,			0,			1.0f);
}

Mat4 Mat4::createScale(const float scale)
{
	return Mat4(	1,	0,	0,	0,
					0,	1,	0,	0,
					0,	0,	1,	0,
					0,	0,	0,	1.0f/scale);
}

Mat4 Mat4::createTranslation(const Vec3& translation)
{
	return Mat4(	1.0f,			0,				0,				0,
					0,				1.0f,			0,				0,
					0,				0,				1.0f,			0,
					translation.x,	translation.y,	translation.z,	1.0f);
}

const float* Mat4::data()
{
	return &columns[0].x;
}

const Vec4& Mat4::operator [](const unsigned int index) const
{
	return columns[index];
}

Mat4 Mat4::operator *(const Mat4& mat4)
{
	return Mat4(    mat4[0][0] * columns[0][0] + mat4[0][1] * columns[1][0] + mat4[0][2] * columns[2][0] + mat4[0][3] * columns[3][0],
					mat4[0][0] * columns[0][1] + mat4[0][1] * columns[1][1] + mat4[0][2] * columns[2][1] + mat4[0][3] * columns[3][1],
					mat4[0][0] * columns[0][2] + mat4[0][1] * columns[1][2] + mat4[0][2] * columns[2][2] + mat4[0][3] * columns[3][2],
					mat4[0][0] * columns[0][3] + mat4[0][1] * columns[1][3] + mat4[0][2] * columns[2][3] + mat4[0][3] * columns[3][3],

					mat4[1][0] * columns[0][0] + mat4[1][1] * columns[1][0] + mat4[1][2] * columns[2][0] + mat4[1][3] * columns[3][0],
					mat4[1][0] * columns[0][1] + mat4[1][1] * columns[1][1] + mat4[1][2] * columns[2][1] + mat4[1][3] * columns[3][1],
					mat4[1][0] * columns[0][2] + mat4[1][1] * columns[1][2] + mat4[1][2] * columns[2][2] + mat4[1][3] * columns[3][2],
					mat4[1][0] * columns[0][3] + mat4[1][1] * columns[1][3] + mat4[1][2] * columns[2][3] + mat4[1][3] * columns[3][3],

					mat4[2][0] * columns[0][0] + mat4[2][1] * columns[1][0] + mat4[2][2] * columns[2][0] + mat4[2][3] * columns[3][0],
					mat4[2][0] * columns[0][1] + mat4[2][1] * columns[1][1] + mat4[2][2] * columns[2][1] + mat4[2][3] * columns[3][1],
					mat4[2][0] * columns[0][2] + mat4[2][1] * columns[1][2] + mat4[2][2] * columns[2][2] + mat4[2][3] * columns[3][2],
					mat4[2][0] * columns[0][3] + mat4[2][1] * columns[1][3] + mat4[2][2] * columns[2][3] + mat4[2][3] * columns[3][3],

					mat4[3][0] * columns[0][0] + mat4[3][1] * columns[1][0] + mat4[3][2] * columns[2][0] + mat4[3][3] * columns[3][0],
					mat4[3][0] * columns[0][1] + mat4[3][1] * columns[1][1] + mat4[3][2] * columns[2][1] + mat4[3][3] * columns[3][1],
					mat4[3][0] * columns[0][2] + mat4[3][1] * columns[1][2] + mat4[3][2] * columns[2][2] + mat4[3][3] * columns[3][2],
					mat4[3][0] * columns[0][3] + mat4[3][1] * columns[1][3] + mat4[3][2] * columns[2][3] + mat4[3][3] * columns[3][3]
				);
}