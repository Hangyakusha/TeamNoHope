#ifndef COLOR_H
#define COLOR_H

namespace gg
{
	class Color
	{
	public:

		Color(float r, float g, float b, float a);
		Color(float r, float g, float b);
		~Color();
		Color(const Color& color);

		float red;
		float green;
		float blue;
		float alpha;
	};
}

#endif