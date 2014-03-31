#ifndef INPUT_H
#define INPUT_H

//#include "android/input.h"

namespace gg
{
	class Input
	{

	public:

		Input();
		~Input();

		static void getKey(int key);

	private:

		Input(Input&);

	};
}

#endif

