#include "Ground.h"

using namespace NoHope;
Ground::Ground(int x, int y, int width, int height, Texture *texture, Shader *shader, b2World* world)
	: GameObject(x,y,width,height,texture,shader,world)
{
	
	rigidbody = new Rigidbody(world, Vec2(x,y), 0, Vec2(width,height), true, true);
}


Ground::~Ground()
{
}
