#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <Box2D\Box2D.h>
#include <math\Vec2.h>
#include <Window.h>
#include <Collision.h>
#define PIXELS_PER_METER 100

namespace NoHope
{
	class Rigidbody : public b2ContactListener
	{
	public:
		Rigidbody(b2World *world,Vec2 position, float angle, Vec2 size);
		~Rigidbody();
		void Init(Vec2 position, float angle, Vec2 size);

		b2World *m_world;

		b2Body *dynamicBody;

		Vec2 getPosition();
		float getAngle();
		void Movement();
		void Ground();
		void Collision();
		bool m_contacting;
		//GameObject* player;

		void startContact() { m_contacting = true; }
		void endContact() { m_contacting = false; }

		virtual void BeginContact(b2Contact* contact);
		virtual void EndContact(b2Contact* contact);
	};
}

#endif