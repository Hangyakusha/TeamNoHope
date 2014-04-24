#include "Camera.h"

using namespace NoHope;

Camera::Camera()
{
	
}

Camera::~Camera() {}

//void Camera::update(float dt)
//{
//	 view;	
//}

//void Camera::draw() {}

void Camera::setCameraPosition(float x, float y)
{
	//this->x = x;
	//this->y = y;
	view = Mat4::createTranslation(Vec3(-x,-y,0.0f));
}

Mat4 Camera::cameraViewMatrix()
{	
	
	
	return view;
}