#include <Player.h>
#include <iostream>

using namespace NoHope;

Player::Player(int x, int y, int width, int height, Texture *texture, Shader *shader, b2World* world)
	: GameObject(x,y,width,height,texture,shader,world)
{
	delete rigidbody;
	rigidbody = new Rigidbody(world, Vec2(x,y), 0, Vec2(width, height), true, false);
	//Vec2(texture->getSize().x*width,texture->getSize().y*height)
	jumpTimeout = 0;
	Vec2 mov = Vec2(x, y);
}

Player::~Player()
{

}
//
//void Player::Init(Vec2 position, float angle, Vec2 size)
//{
//	b2BodyDef myBodyDef;
//	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
//
//	position = position / PIXELS_PER_METER;
//	size = size / PIXELS_PER_METER;
//
//	myBodyDef.position.Set(position.x, position.y); //set the starting position
//	myBodyDef.angle = angle; //set the starting angle
//
//	dynamicBody = m_world->CreateBody(&myBodyDef); 
//
//	b2PolygonShape dynamicBox;
//
//	dynamicBox.SetAsBox(size.x/2,size.y/2);
//  
//	b2FixtureDef boxFixtureDef;
//	boxFixtureDef.shape = &dynamicBox;
//	boxFixtureDef.density = 10;
//
//	dynamicBody->CreateFixture(&boxFixtureDef);
//}

void Player::update(float dt)
{
	//std::cout <<"r x: "<<rigidbody->getPosition().x << "r y: "<<rigidbody->getPosition().y << std::endl;
	setRotationZ(rigidbody->getAngle());

	movement(dt);
	jumping(dt);
	
	if(rigidbody->getPosition().y < -30)
	{
		setPosition(100,100);
		rigidbody->setPosition(Vec2(100,100));
		Vec2 t = rigidbody->getPosition();
		mov.x = 0.f;
		mov.y = 0.f;
	}
	else
	{
	setPosition(rigidbody->getPosition());
	}	
	
	//std::cout<<rigidbody->body->GetLinearVelocity().x << std::endl;
}


void Player::movement(float dt)
{
	float x = 0.f;
	float y = 0.f;

	
	mov.x = 0.f;
	mov.y = 0.f;

	b2Vec2 vel = rigidbody->body->GetLinearVelocity();
	float MAX_VEL = 5.f; //max 120 dunno why
	//std::cout << vel.x << std::endl;

	if(vel.x > MAX_VEL)
	{
		rigidbody->body->SetLinearVelocity(b2Vec2(MAX_VEL,vel.y));
		//std::cout << "dangerzone" << std::endl;
	}

	else if(vel.x < -MAX_VEL)
	{
		rigidbody->body->SetLinearVelocity(b2Vec2(-MAX_VEL,vel.y));
		//std::cout << "dangerzone" << std::endl;
	}

	//MOVEMENT

	//W - Up
	if(Window::getKey(87))
	{
		mov.x += 0.f;
		mov.y += 2.f;
	}
	//A - Left
	if(Window::getKey(65))
	{
		mov.x += -2.f;
		mov.y += 0.f;	
	}
	//S - Down
	if(Window::getKey(83))
	{	
		mov.x += 0.f;
		mov.y += -2.f;
	}
	//D - Right
	if(Window::getKey(68))
	{	
		mov.x += 2.f;
		mov.y += 0.f;
	}

	rigidbody->SetLinearImpulse(mov);
}

void Player::jumping(float dt)
{
	isJumping = false;
	if (jumpTimeout >= 1)
		{
			jumpTimeout--;
		}	
	float ux = 0.f;
	float uy = 0.0f;
	Vec2 up = Vec2(ux, uy);
	
	float px = 0.f;
	float py = 0.f;

	Vec2 paljon = Vec2(px, py);

	if(Window::getKey(32) && jumpTimeout == 0) //Space
	{
		paljon.x = 0.f;
		paljon.y = 80.f;
		isJumping = true;
		jumpTimeout = 65;
	/*	up.x = 50.f;
		up.y = 50.f;*/
		//dynamicBody->ApplyLinearImpulse(b2Vec2(0, dynamicBody->GetMass() * 1000), dynamicBody->GetWorldCenter());	
	}
	/*std::cout<<isJumping<<std::endl;*/

	//else
	//{
	// isJumping = false;
	//}

	

	rigidbody->SetLinearImpulse(paljon);
	//std::cout<<jumpTimeout<<std::endl;

}

//velocity