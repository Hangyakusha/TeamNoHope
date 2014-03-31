#include <Rigidbody.h>
#include <iostream>

using namespace NoHope;


Rigidbody::Rigidbody(b2World *world,Vec2 position, float angle, Vec2 size)
	:m_world(world) , 
	m_contacting(false)
{
	Init(position, angle, size);
	
}

Rigidbody::~Rigidbody()
{
	m_world->DestroyBody(dynamicBody);
}


void Rigidbody::Init(Vec2 position, float angle, Vec2 size)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body

	position = position / PIXELS_PER_METER;
	size = size / PIXELS_PER_METER;

	myBodyDef.position.Set(position.x, position.y); //set the starting position
	myBodyDef.angle = angle; //set the starting angle

	dynamicBody = m_world->CreateBody(&myBodyDef); 

	b2PolygonShape dynamicBox;

	dynamicBox.SetAsBox(size.x/2,size.y/2);
  
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &dynamicBox;
	boxFixtureDef.density = 10;

	dynamicBody->CreateFixture(&boxFixtureDef);


}

void Rigidbody::Ground()
{
	b2BodyDef groundBodyDef;

	groundBodyDef.position.Set(0.0f, -10.0f);
	
	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;

	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);



}
Vec2 Rigidbody::getPosition()
{
	const b2Vec2 pos = dynamicBody->GetPosition();
	Vec2 retVal = Vec2(pos.x,pos.y);
	retVal = retVal * PIXELS_PER_METER;
	return retVal;
}

float Rigidbody::getAngle()
{
	return dynamicBody->GetAngle();
}

//class MyContactListener
//{
    void BeginContact(b2Contact* contact) 
	{
  
      //check if fixture A was a player
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
		  static_cast<Rigidbody*>( bodyUserData )->startContact();
  
      //check if fixture B was ground
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Rigidbody*>( bodyUserData )->startContact();
  
    }
  
    void EndContact(b2Contact* contact) 
	{
  
      //check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Rigidbody*>( bodyUserData )->endContact();
  
      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
        static_cast<Rigidbody*>( bodyUserData )->endContact(); 
	}
//};

void Rigidbody::Movement()
{
	dynamicBody->SetFixedRotation(true);
	m_contacting=false;

	//if(m_contacting == true)
	//{
	//	std::cout<<"Koskee!"<<std::endl;
	//}


	float x = 0.f;
	float y = 0.f;
	b2Vec2 mov = b2Vec2(x, y);

	float ux = 0.f;
	float uy = 0.0f;

	b2Vec2 up = b2Vec2(ux, uy);

	float px = 0.f;
	float py = 0.f;

	b2Vec2 paljon = b2Vec2(px, py);

	if(Window::getKey(87))
	{
		mov.x = 0.f;
		mov.y = 1.f;
	}

	if(Window::getKey(65))
	{
		mov.x = -1.f;
		mov.y = 0.f;	
	}

	if(Window::getKey(83))
	{	
		mov.x = 0.f;
		mov.y = -1.f;
	}

	if(Window::getKey(68))
	{	
		mov.x = 1.f;
		mov.y = 0.f;
	}

	if(Window::getKey(32)) //Space
	{
		paljon.x = 0.f;
		paljon.y = 40.f;
		up.x = 50.f;
		up.y = 50.f;
		m_contacting = true;
		std::cout << "m_contacting: "<< m_contacting << std::endl;
		std::cout << "space stna" << std::endl;
		//dynamicBody->ApplyLinearImpulse(b2Vec2(0, dynamicBody->GetMass() * 1000), dynamicBody->GetWorldCenter());	
	}

	std::cout << "m_contacting: "<< m_contacting << std::endl;

	dynamicBody->SetLinearVelocity(mov);
	dynamicBody->ApplyLinearImpulse(paljon, up);
	
}
