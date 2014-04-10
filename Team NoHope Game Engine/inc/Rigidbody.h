#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <Box2D\Box2D.h>
#include <math\Vec2.h>
#include <Window.h>


#define PIXELS_PER_METER 100



namespace NoHope
{

	class Rigidbody /*: public b2ContactListener*/
	{
	public:
		Rigidbody(b2World *world, Vec2 position, float angle, Vec2 size, bool fixedRotation, bool staticBody);
		~Rigidbody();
		void Init(Vec2 position, float angle, Vec2 size, bool fixedR, bool staticB);

		b2World *m_world;

		b2Body *body;
		void setPosition(Vec2 spos);
		Vec2 getPosition();
		float getAngle();

		void SetLinearVelocity(Vec2 linearV);
		void SetLinearImpulse(Vec2 LinearI);
		
		//void Movement(Vec2 linearVelocity, Vec2 linearImpulse);

		//bool m_contacting;


		//void startContact() { m_contacting = true; }
		//void endContact() { m_contacting = false; }
		
		/*body->SetUserData( this );*/
	

		
	};
}

#endif