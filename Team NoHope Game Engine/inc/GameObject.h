#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SpriteEntity.h>
#include <Rigidbody.h>
#include <Box2D\Box2D.h>

namespace NoHope
{
class GameObject : public SpriteEntity
{
	public:

			GameObject(int x, int y, int width, int height, Texture *texture, Shader *shader, b2World* world);
			virtual ~GameObject();

			Rigidbody *rigidbody;

			b2World *m_world;

			virtual void update(float dt);
			
			//void init();

			//Rigidbody *playerBody;
			//Rigidbody *groundBody;
};

//m_world->SetContactListener(&myContactListenerInstance);
//GameObject myContactListenerInstance;
}
#endif