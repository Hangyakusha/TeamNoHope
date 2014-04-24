#include <Enemy.h>

using namespace NoHope;

Enemy::Enemy(int x, int y, int width, int height, Texture *texture, Shader *shader, b2World* world)
	: GameObject(x,y,width,height,texture,shader,world)
{

	rigidbody = new Rigidbody(world, Vec2(x,y), 0, Vec2(width, height), true, false);
	//Vec2(texture->getSize().x*width,texture->getSize().y*height)
	jumpTimeout = 0;
	Vec2 movs = Vec2(x, y);
}

Enemy::~Enemy()
{

}

void Enemy::update(float dt)
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
		movs.x = 0.f;
		movs.y = 0.f;
	}
	else
	{
	setPosition(rigidbody->getPosition());
	}	
	
	//std::cout<<rigidbody->body->GetLinearVelocity().x << std::endl;
}


void Enemy::movement(float dt)
{
	float x = 0.f;
	float y = 0.f;

	movs.x = 0.f;
	movs.y = 0.f;

	b2Vec2 vels = rigidbody->body->GetLinearVelocity();
	float MAX_VEL = 5.f; //max 120 dunno why
	//std::cout << vel.x << std::endl;

	if(vels.x > MAX_VEL)
	{
		rigidbody->body->SetLinearVelocity(b2Vec2(MAX_VEL,vels.y));
		//std::cout << "dangerzone" << std::endl;
	}

	else if(vels.x < -MAX_VEL)
	{
		rigidbody->body->SetLinearVelocity(b2Vec2(-MAX_VEL,vels.y));
		//std::cout << "dangerzone" << std::endl;
	}

	//MOVEMENT

	//W - Up
	if(Window::getKey(265))
	{
		movs.x += 0.f;
		movs.y += 2.f;
		setScale(Vec3(1,-1,1));
	}
	//A - Left
	if(Window::getKey(263))
	{
		movs.x += -2.f;
		movs.y += 0.f;
		setScale(Vec3(-1,1,1));
	}
	//S - Down
	if(Window::getKey(264))
	{	
		movs.x += 0.f;
		movs.y += -2.f;
		setScale(Vec3(1,1,1));
		
	}
	//D - Right
	if(Window::getKey(262))
	{	
		movs.x += 2.f;
		movs.y += 0.f;
		setScale(Vec3(1,1,1));
		
	}

	rigidbody->SetLinearImpulse(movs);
}

void Enemy::jumping(float dt)
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

	if(Window::getKey(257) && jumpTimeout == 0) //Space
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