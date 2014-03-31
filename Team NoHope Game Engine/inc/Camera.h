#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"

namespace NoHope
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