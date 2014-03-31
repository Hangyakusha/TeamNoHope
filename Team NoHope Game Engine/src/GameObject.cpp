#include <GameObject.h>

using namespace NoHope;

GameObject::GameObject(int x, int y, int width, int height, Texture *texture, Shader *shader, b2World* world)
	:SpriteEntity(x, y, width, height, texture, shader)
{
	rigidbody = new Rigidbody(world, Vec2(x,y), 0, Vec2(width,height));
}

GameObject::~GameObject()
{

}

void GameObject::update(float dt)
{
	setPosition(rigidbody->getPosition());

	setRotationZ(rigidbody->getAngle());

	rigidbody->Movement();

	rigidbody->startContact();
	rigidbody->endContact();
}