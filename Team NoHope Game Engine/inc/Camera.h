#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "math\Mat4.h"

namespace NoHope
{
	class Camera
	{
	public:

		Camera();
		~Camera();

		/*void draw();*/
		/*void update(float dt);*/
		void setCameraPosition(float x,float y);
		Mat4 cameraViewMatrix();
		Mat4 view;

	private:
		/*float x,y;*/
		Camera(Camera&);

	};
}

#endif