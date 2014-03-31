#include "Color.h"

using namespace NoHope;

Color::Color(float r, float g, float b, float a):
	red(r),
	green(g),
	blue(b),
	alpha(a)
{
}

Color::Color(float r, float g, float b):
red(r),
green(g),
blue(b),
alpha(1.0f)
{
}

Color::~Color() {}

Color::Color(const Color& color):
	red(color.red),
	green(color.green),
	blue(color.blue),
	alpha(color.alpha)
{
}