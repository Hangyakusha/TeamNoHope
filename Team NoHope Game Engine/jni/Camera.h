#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"

namespace gg
{
	class Camera : public Entity
	{
	public:

		Camera();
		~Camera();

		virtual void draw();
		virtual void update(float dt);

	private:

		Camera(Camera&);

	};
}

#endif