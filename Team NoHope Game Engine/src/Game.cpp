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

	issco = 0;
	sepsco = 0;
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
	
	

	Texture* _player = Texture::load(Util::resourcePath + "Seppo.tga");	
	Texture* _enemy = Texture::load(Util::resourcePath + "Ismo.tga");
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
	
	enemy = new NoHope::Enemy(371,598,64,128, _enemy, _shader, &world);
	enemy->setProjectionMatrix(_projection);

	ground = new NoHope::Ground(0,0,412,64, _ground, _shader, &world);
	ground->setProjectionMatrix(_projection);

	ground2 = new NoHope::Ground(700,100,412,64, _ground2, _shader, &world);
	ground2->setProjectionMatrix(_projection);
	//_sound->play();

	ground3 = new NoHope::Ground(1200,300,412,64, _ground3, _shader, &world);
	ground3->setProjectionMatrix(_projection);

	ground4 = new NoHope::Ground(500,500,412,64, _ground4, _shader, &world);
	ground4->setProjectionMatrix(_projection);



	sky = new NoHope::Ground(0,800,412,64, _sky, _shader, &world);
	sky->setProjectionMatrix(_projection);
	fpsTimer = 0.f;
	
	bg = new NoHope::SpriteEntity(0,0, Graphics::screenWidth*3, Graphics::screenHeight*3, _bg, _shader);
	bg->setProjectionMatrix(_projection);

	_projection = Mat4(	2.0f / Graphics::screenWidth,	0,												0,		0,
						0,								-2.0f / Graphics::screenHeight,					0,		0,
						0,								0,												0,		0,
						-1,								1,												0,		1);

	text = new NoHope::Text("Vera.ttf", 40);
	text->SetText(L"FPS:");
	//text->AddText(L"\nJEFFREY FTW",Vec4(1,0,0,1));
	text->setPosition(10, 20);
	text->setProjectionMatrix(_projection);

	SeppoText = new NoHope::Text("Vera.ttf", 20);
	SeppoText->SetText(L"Seppo Score:");

	SeppoText->setPosition(500,20);
	SeppoText->setProjectionMatrix(_projection);

	IsmoText = new NoHope::Text("Vera.ttf", 20);
	IsmoText->SetText(L"Ismo Score:");	
	IsmoText->setPosition(800,20);
	IsmoText->setProjectionMatrix(_projection);

	WinText = new NoHope::Text("Vera.ttf", 20);

	WinText->setPosition(Graphics::screenWidth/2, Graphics::screenHeight/4);
	WinText->setProjectionMatrix(_projection);

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
	SeppoText->SetText(L"Seppo Score:" + std::to_wstring((long long)sepsco));


	IsmoText->SetText(L"Ismo Score:" + std::to_wstring((long long)issco));
	
	if(issco > 3)
	{
		WinText->SetText(L"ISMO WINS",Vec4(0,0,0,1));
		issco = 0;
		sepsco = 0;
	}
	if(sepsco > 3)		
	{
		
		WinText->SetText(L"SEPPO WINS",Vec4(0,0,0,1));
		sepsco = 0;
		issco = 0;
	}

	if(sepsco > 0 || issco > 0)
	{
		
		WinText->SetText(L" ",Vec4(0,0,0,1));
		sepsco = 0;
		issco = 0;
	}

	_shader->setUniform("time", _timer);
	
	const float timeStep = 1.f/60.f;
	//if (_timer > timeStep)
	//{
		//_timer = 0.f;
		world.Step(timeStep, 8, 3);
	//}
	player->update(dt);
	enemy->update(dt);
	
	//std::cout <<"p x: "<<player->getPosition().x << "p y: "<<player->getPosition().y << std::endl;
	_camera.setCameraPosition(player->getPosition().x - 640.0f, player->getPosition().y - 360 );
	fps++;

	if(player->getPosition().y == 100 && player->getPosition().x == 100 )
	{
		issco++;
	}

	if(enemy->getPosition().y == 100 && enemy->getPosition().x == 100)
	{
		sepsco++;
	}

}

void Game::render() 
{
	_graphics->clear(0.2f, 0.2f, 0.2f);
	renderTexture->clear(Color(0.95f, 0.95f, 0.95f));

	renderTexture->draw(*bg, _camera);

	renderTexture->draw(*ground, _camera);
	renderTexture->draw(*ground2, _camera);
	renderTexture->draw(*ground3, _camera);
	renderTexture->draw(*ground4, _camera);

	renderTexture->draw(*sky, _camera);

	renderTexture->draw(*player, _camera);
	renderTexture->draw(*enemy, _camera);

	renderTexture->draw(*text, _camera);
	renderTexture->draw(*SeppoText, _camera);
	renderTexture->draw(*IsmoText, _camera);
	renderTexture->draw(*WinText, _camera);

	renderTexture->display();
	
}