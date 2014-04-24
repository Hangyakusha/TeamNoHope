#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>

#include "Debug.h"
#include "Game.h"
#include "Util.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
//#include "Sound.h"

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
	delete player;
	delete ground;
	delete ground2;
	delete ground3;
	delete ground4;
	delete sky;
	delete text;
	delete bg;

}

void Game::init()
{
	//3D
	Shader* _shader3D = new Shader(Util::resourcePath + "Shaders/basicd.vert", 
							Util::resourcePath +  "Shaders/basicd.frag");
	
	
	//if(Player::playerDirection == false)
	//{
	Texture* _player = Texture::load(Util::resourcePath + "SeppoBack.tga");
	//}
	/*Texture* _player = Texture::load(Util::resourcePath + "Seppo.tga");*/
	
	//Texture* _enemy = Texture::load(Util::resourcePath + "Char_1.tga");
	Texture *_ground = Texture::load(Util::resourcePath + "pitkaplatta.tga");
	Texture *_ground2 = Texture::load(Util::resourcePath + "pitkaplatta.tga");
	Texture *_ground3 = Texture::load(Util::resourcePath + "pitkaplatta.tga");
	Texture *_ground4 = Texture::load(Util::resourcePath + "pitkaplatta.tga");
	Texture *_sky = Texture::load(Util::resourcePath + "pitkaplatta.tga");
	Texture *_bg = Texture::load(Util::resourcePath + "Backgruund.tga");


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


	player = new NoHope::Player(100,100, 64, 128, _player, _shader, &world);
	/*player->setPosition(Graphics::screenWidth/2, Graphics::screenHeight/2);*/
	//player->setPosition(300,300);
	player->setProjectionMatrix(_projection);
	
	ground = new NoHope::Ground(0,0,412,64, _ground, _shader, &world);
	ground->setProjectionMatrix(_projection);

	ground2 = new NoHope::Ground(700,100,412,64, _ground2, _shader, &world);
	ground2->setProjectionMatrix(_projection);
	//_sound->play();

	ground3 = new NoHope::Ground(1200,300,412,64, _ground3, _shader, &world);
	ground3->setProjectionMatrix(_projection);

	ground4 = new NoHope::Ground(500,500,412,64, _ground4, _shader, &world);
	ground4->setProjectionMatrix(_projection);

	//enemy = new NoHope::Player(510,510,64,128, _ground4, _shader, &world);
	//enemy->setProjectionMatrix(_projection);

	sky = new NoHope::Ground(0,800,412,64, _sky, _shader, &world);
	sky->setProjectionMatrix(_projection);
	fpsTimer = 0.f;
	
	bg = new NoHope::SpriteEntity(Graphics::screenWidth/2, Graphics::screenHeight/2, 1280, 720, _bg, _shader);
	bg->setProjectionMatrix(_projection);

	_projection = Mat4(	2.0f / Graphics::screenWidth,	0,												0,		0,
						0,								-2.0f / Graphics::screenHeight,					0,		0,
						0,								0,												0,		0,
						-1,								1,												0,		1);

	text = new NoHope::Text("Vera.ttf", 40);
	text->SetText(L"FPS:");
	text->AddText(L"\nJEFFREY FTW",Vec4(1,0,0,1));
	text->setPosition(10, 20);
	text->setProjectionMatrix(_projection);
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
		text->SetText(L"FPS:" + std::to_wstring((long long)fps));
		//long long intil hyvä
		//unsigned long long unsigned int
		//long double double tai float

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
	_camera.setCameraPosition(player->getPosition().x - 640.0f, player->getPosition().y - 360 );
	fps++;
}

void Game::render() 
{
	_graphics->clear(0.2f, 0.2f, 0.2f);
	renderTexture->clear(Color(0.95f, 0.95f, 0.95f));
	renderTexture->draw(*bg,_camera);
	renderTexture->draw(*ground,_camera);
	renderTexture->draw(*ground2,_camera);
	renderTexture->draw(*ground3,_camera);
	renderTexture->draw(*ground4,_camera);
	renderTexture->draw(*sky,_camera);
	renderTexture->draw(*player,_camera);
	renderTexture->draw(*text,_camera);
	/*renderTexture->draw(*enemy);*/
	renderTexture->display();
	
}