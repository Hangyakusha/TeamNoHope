#include <iostream>
#include <GameObject.h>


using namespace NoHope;

GameObject::GameObject(int x, int y, int width, int height, Texture *texture, Shader *shader, b2World* world)
	:SpriteEntity(x, y, width, height, texture, shader)
{
	rigidbody = new Rigidbody(world, Vec2(x,y), 0, Vec2(texture->getSize().x*width,texture->getSize().y*height), false, false);
	//
	//Vec2(width, height)
}

GameObject::~GameObject()
{
	delete rigidbody;
	//m_world->DestroyBody(playerBody);
	//m_world->DestroyBody(groundBody);
}

void GameObject::update(float dt)
{
	////setPosition(rigidbody->getPosition());

	////setRotationZ(rigidbody->getAngle());

	//////rigidbody->Movement();

	//////rigidbody->startContact();
	//////rigidbody->endContact();

	////std::cout<<"gg"<<std::endl;

		


}




//void GameObject::init()
//{
//	 rigidbody->playerBody = m_world->CreateBody(&playerBodyDef);
//	rigidbody->groundBody = m_world->CreateBody(&groundBodyDef);
//
//}
//global scope
// MyContactListener myContactListenerInstance;

			//FooTest

//constructor
// m_world->SetContactListener(&myContactListenerInstance);
//body

			//MyContactListener

 //class MyContactListener : public b2ContactListener
  //{
    //void BeginContact(b2Contact* contact) {
  
      ////check if fixture A was a ball
      //void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      //if ( bodyUserData )
        //static_cast<Ball*>( bodyUserData )->startContact();
  
      ////check if fixture B was a ball
      //bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      //if ( bodyUserData )
        //static_cast<Ball*>( bodyUserData )->startContact();  
    //}
    //void EndContact(b2Contact* contact) {
  
      //check if fixture A was a ball
      //void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      //if ( bodyUserData )
        //static_cast<Ball*>( bodyUserData )->endContact();
  
      //check if fixture B was a ball
      //bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      //if ( bodyUserData )
       // static_cast<Ball*>( bodyUserData )->endContact();  
    //}
 // };

				//Ball

//constructor
//m_contacting = false;

//h
//  void startContact() { m_contacting = true; }
// void endContact() { m_contacting = false; }
// bool m_contacting;


//create ball outside and before foo