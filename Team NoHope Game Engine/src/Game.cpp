#include <iostream>

#include "Debug.h"
#include "Game.h"
#include "Util.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
//#include "Sound.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>

#include <AL/al.h>
#include <AL/alc.h>


using namespace NoHope;

Game::Game(int width, int height)
	:world(b2Vec2(0.0f, -20.0f))
{
	_graphics = new Graphics(width, height);
	init();
	writeLog("WIDTH: %d, HEIGHT: %d", Graphics::screenWidth, Graphics::screenHeight);
}

Game::~Game()
{
    delete _graphics;
	delete _shader;
}

void Game::init()
{
	//3D
	Shader* _shader3D = new Shader(Util::resourcePath + "Shaders/basicd.vert", 
							Util::resourcePath +  "Shaders/basicd.frag");

	Texture* _player = Texture::load(Util::resourcePath + "ufo.tga");
	Texture *_ground = Texture::load(Util::resourcePath + "testing.tga");
	Texture *_ground2 = Texture::load(Util::resourcePath + "bg.tga");
	Texture *_sky = Texture::load(Util::resourcePath + "bg.tga");
	_shader = new Shader(Util::resourcePath + "Shaders/basic.vert", 
							Util::resourcePath +  "Shaders/basic.frag");

	renderTexture = new RenderTexture();

	fps = 0;
	_timer = 0.0f;
	srand(time(NULL));

	_projection = Mat4(	2.0f / Graphics::screenWidth,	0,												0,		0,
						0,								2.0f / Graphics::screenHeight,					0,		0,
						0,								0,												0,		0,
						-1,								-1,												0,		1);

	float nearZ = 2;
	float farZ = 100;
	float fov = 45.0f;
	float aspect = Graphics::aspectRatio;
	float f = 1/tan(fov/2.0f);

	_projection3D = Mat4(	f / aspect,			0,					0,							0,
							0,					f,					0,							0,
							0,					0,					-((farZ+nearZ)/(farZ-nearZ)),	-1,
							0,					0,					-(2*farZ*nearZ/(farZ-nearZ)),	0);


	player = new NoHope::Player(100,100, 64, 64, _player, _shader, &world);
	/*player->setPosition(Graphics::screenWidth/2, Graphics::screenHeight/2);*/
	//player->setPosition(300,300);
	player->setProjectionMatrix(_projection);
	
	ground = new NoHope::Ground(0,0,400,10, _ground, _shader, &world);
	ground->setProjectionMatrix(_projection);

	ground2 = new NoHope::Ground(700,100,400,20, _ground2, _shader, &world);
	ground2->setProjectionMatrix(_projection);
	//_sound->play();

	sky = new NoHope::Ground(0,300,2600,50, _sky, _shader, &world);
	sky->setProjectionMatrix(_projection);
	fpsTimer = 0.f;
}

void Game::addSprite(int x, int y, int dirX, int dirY)
{
	Sprite sprite;
	sprite.entity = new SpriteEntity(x, y, 64, 64, texture, _shader);
	sprite.entity->setProjectionMatrix(_projection);
	Vec2 dir = Vec2(dirX, dirY);
	dir.normalize();
	sprite.direction = dir;   
	sprite.speed = Util::randomRange(200, 300);
	sprites.push_back(sprite);
	//_sound2->play();
}

void Game::update(float dt) 
{
	fpsTimer += dt;
	_timer += dt/20;
	//writeLog("dt %f\n",dt);
	if(fpsTimer > 1)
	{
		writeLog("FPS:%d\n", fps);
		fpsTimer = 0;
		fps = 0;
	}

	_shader->setUniform("time", _timer);
	
	const float timeStep = 1.f/60.f;
	//if (_timer > timeStep)
	//{
		//_timer = 0.f;
		world.Step(timeStep, 8, 3);
	//}
	player->update(dt);

	//std::cout <<"p x: "<<player->getPosition().x << "p y: "<<player->getPosition().y << std::endl;
	
	fps++;
}

void Game::render() 
{
	_graphics->clear(0.2f, 0.2f, 0.2f);
	renderTexture->clear(Color(0.95f, 0.95f, 0.95f));

	renderTexture->draw(*ground);
	renderTexture->draw(*ground2);
	renderTexture->draw(*sky);
	renderTexture->draw(*player);
	
	renderTexture->display();
}