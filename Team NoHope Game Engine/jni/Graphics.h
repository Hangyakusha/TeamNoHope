#ifndef GRAPHICS_H
#define GRAPHICS_H

namespace gg
{
	class Graphics
	{

	public:

		Graphics(int width, int height);
		~Graphics();

		void clear(float r, float g, float b) const;

		static int screenWidth;
		static int screenHeight;
		static float aspectRatio;

	private:

		void init();
	};
}

#endif