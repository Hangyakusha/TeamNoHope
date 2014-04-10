#include <Rigidbody.h>
#include <iostream>

using namespace NoHope;


Rigidbody::Rigidbody(b2World *world, Vec2 position, float angle, Vec2 size, bool fixedRotation, bool staticBody)
	:m_world(world)
{
	Init(position, angle, size, fixedRotation, staticBody);
	
}

Rigidbody::~Rigidbody()
{
	m_world->DestroyBody(body);
	//m_world->DestroyBody(groundBody);
}


void Rigidbody::Init(Vec2 position, float angle, Vec2 size, bool fixedR, bool staticBody)
{
	//Player

	b2BodyDef BodyDef;
	if (!staticBody)
	{
		BodyDef.type = b2_dynamicBody; //this will be a dynamic body
	}

	position = position / PIXELS_PER_METER;
	size = size / PIXELS_PER_METER;

	BodyDef.position.Set(position.x, position.y); //set the starting position
	BodyDef.angle = angle; //set the starting angle

	body = m_world->CreateBody(&BodyDef);

	b2PolygonShape dynamicBox;

	dynamicBox.SetAsBox((size.x/2),(size.y/2));
	//dynamicBox.SetAsBox(size.x/2,size.y/2);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &dynamicBox;
	boxFixtureDef.density = 10;

	body->CreateFixture(&boxFixtureDef);

	body->SetFixedRotation(fixedR);
	
	//Ground

	//b2BodyDef groundBodyDef;
	////groundBodyDef.type = b2_staticBody;

	//groundBodyDef.position.Set(0.0f, -10.0f);
	//
	//groundBody = m_world->CreateBody(&groundBodyDef);

	//b2PolygonShape groundBox;

	//groundBox.SetAsBox(50.0f, 10.0f);

	//groundBody->CreateFixture(&groundBox, 0.0f);
}


void Rigidbody::setPosition(Vec2 spos) //Jessen kommentit
{
	const b2Vec2 Spos(spos.x/PIXELS_PER_METER , spos.y/PIXELS_PER_METER);
	body->SetTransform(Spos,0);
}

Vec2 Rigidbody::getPosition()
{
	const b2Vec2 pos = body->GetPosition();
	Vec2 retVal = Vec2(pos.x,pos.y);
	retVal = retVal * PIXELS_PER_METER;
	return retVal;
}

float Rigidbody::getAngle()
{
	return body->GetAngle();
}

void Rigidbody::SetLinearVelocity(Vec2 linearV)
{
	body->SetLinearVelocity(b2Vec2(linearV.x,linearV.y));
}
void Rigidbody::SetLinearImpulse(Vec2 LinearI)
{
	body->ApplyLinearImpulse(b2Vec2(LinearI.x,LinearI.y), b2Vec2(0,1));
}

//
//void BeginContact(b2Contact* contact) 
//{
//  
//     //check if fixture A was a ball
//     void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
//     if ( bodyUserData )
//     static_cast<Rigidbody*>( bodyUserData )->startContact();
//  
//     //check if fixture B was a ball
//     bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
//     if ( bodyUserData )
//     static_cast<Rigidbody*>( bodyUserData )->startContact();
//  
//}
//  
//void EndContact(b2Contact* contact) 
//{
//	//check if fixture A was a ball
//	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
//	if ( bodyUserData )
//    static_cast<Rigidbody*>( bodyUserData )->endContact();
//
//	//check if fixture B was a ball
//	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
//	if ( bodyUserData )
//    static_cast<Rigidbody*>( bodyUserData )->endContact();
//
//}