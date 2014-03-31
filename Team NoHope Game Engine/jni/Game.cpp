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

using namespace gg;

Game::Game(int width, int height)
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

	Texture* _tex = Texture::load(Util::resourcePath + "green.tga");
	Texture* _sammichTex = Texture::load(Util::resourcePath + "axe.tga");
	Texture* _heavyTex = Texture::load(Util::resourcePath + "pyro_flat.tga");

	_heavy = new Mesh(_shader3D, Util::resourcePath + "pyro.obj", _heavyTex);
	_sammich = new Mesh(_shader3D, Util::resourcePath + "axe.obj", _sammichTex);
	
	//_cube = new Mesh(_shader3D, Util::resourcePath + "torus.obj", _tex);
	//_cube2 = new Mesh(_shader3D, Util::resourcePath + "monkey.obj", _tex);
	//_cube3 = new Mesh(_shader3D, Util::resourcePath + "torus.obj", _tex);
	
	_heavy->setPosition(0, 0, -10);
	_sammich->setPosition(0, 0, -10);
	//_cube->setPosition(0, 0, -10);
	//_cube2->setPosition(0, 0, -10);
	//_cube3->setPosition(0, 0, -10);
	
	_sammich->setScale(0.3f);
	_heavy->setScale(0.3f);
	//_cube->setScale(2);
	//_cube3->setScale(3.5f);
	//_cube->setScale(10);

	//_sound = Sound::load(Util::resourcePath + "ruby.ogg");
	//_sound2 = Sound::load(Util::resourcePath + "hit.ogg");

	_shader = new Shader(Util::resourcePath + "Shaders/basic.vert", 
							Util::resourcePath +  "Shaders/basic.frag");

	renderTexture = new RenderTexture();

	fps = 0;
	_timer = 0.0f;
	srand(time(NULL));

	texture = Texture::load(Util::resourcePath + "green.tga");

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

	for(int i = 0; i < 10; i++)
	{
		Sprite sprite;
		sprite.entity = new SpriteEntity(Util::randomRange(0, Graphics::screenWidth), Util::randomRange(0, Graphics::screenHeight), 64, 64, texture, _shader);
		Vec2 dir = Vec2(Util::random() - Util::random(), Util::random() - Util::random());
		dir.normalize();
		sprite.direction = dir;
		sprite.speed = Util::randomRange(200, 300);
		sprite.entity->setProjectionMatrix(_projection);
		sprites.push_back(sprite);
	}

	sprite = new gg::SpriteEntity(0, 0, 128, 128, texture, _shader);
	sprite->setPosition(Graphics::screenWidth/2, Graphics::screenHeight/2);
	sprite->setProjectionMatrix(_projection);

	//_cube->setProjectionMatrix(_projection3D);
	//_cube2->setProjectionMatrix(_projection3D);
	//_cube3->setProjectionMatrix(_projection3D);
	_heavy->setProjectionMatrix(_projection3D);
	_sammich->setProjectionMatrix(_projection3D);

	//_sound->play();
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
	static float fpsTimer = 0;
	fpsTimer += dt;
	_timer += dt;

	if(fpsTimer > 1)
	{
		writeLog("FPS:%d, SPRITES:%d\n", fps, sprites.size());
		fpsTimer = 0;
		fps = 0;
	}

	_shader->setUniform("time", _timer);

	for(int i = 0; i < sprites.size(); i++)
	{
		if (sprites[i].entity->getPosition().y < 0)
		{
			sprites[i].entity->setPosition(sprites[i].entity->getPosition().x, 0);
			sprites[i].direction.y *= -1;
		}
		else if (sprites[i].entity->getPosition().y > Graphics::screenHeight)
		{
			sprites[i].entity->setPosition(sprites[i].entity->getPosition().x, Graphics::screenHeight);
			sprites[i].direction.y *= -1;
		}
		if(sprites[i].entity->getPosition().x < 0)
		{
			sprites[i].entity->setPosition(0, sprites[i].entity->getPosition().y);
			sprites[i].direction.x *= -1;
		}
		else if (sprites[i].entity->getPosition().x > Graphics::screenWidth)
		{
			sprites[i].entity->setPosition(Graphics::screenWidth, sprites[i].entity->getPosition().y);
			sprites[i].direction.x *= -1;
		}

		sprites[i].entity->setPosition( sprites[i].entity->getPosition() + 
									sprites[i].direction * 
									sprites[i].speed * 
									dt);

		sprites[i].entity->setRotationZ(sin(_timer*(i/10.0f))+(i/500.0f));
		//sprites[i].entity->setScale(sin(_timer*((i/500.0f)*10)) + 1.5f);
	}

	//sprite->setRotation(_timer);
	//_cube2->setPosition(_cube2->getPosition() + Vec3(sin(_timer*3)/10, 0, cos(_timer*3)/10));
	//_cube2->setRotation(_timer*10);
	//_cube->setRotation(_timer);
	//_cube3->setRotation(-_timer*3);
	_heavy->setRotationY(_timer);
	//_sammich->setPosition(_sammich->getPosition() + Vec3(sin(_timer*3)/5, 0, cos(_timer*3)/15));
	_sammich->setPosition(Vec3(-3, 0, -10));
	_sammich->setRotationY(_timer);
	//_cube->setScale(sin(_timer*7) + 1.5f);
	//_cube->setPosition(Vec3(sin(_timer)*2, _cube->getPosition().y, _cube->getPosition().z));
	//sprite->setPosition(Vec3(sprite->getPosition().x, sprite->getPosition().y, sin(_timer)*100));
	sprite->setScale(sin(_timer*7) + 1.5f);
    sprite->setRotationZ(_timer);
	fps++;
}

void Game::render() 
{
	_graphics->clear(0.2f, 0.2f, 0.2f);
	renderTexture->clear(Color(0.95f, 0.95f, 0.95f));

	//renderTexture->draw(*_cube);
	//renderTexture->draw(*_cube2);
	//renderTexture->draw(*_cube3);
	renderTexture->draw(*_heavy);

	for(int i = 0; i < sprites.size(); i++)
	{
        //renderTexture->draw(*sprites[i].entity);
	}

	renderTexture->display();

	//_cube->draw();
	//_cube2->draw();
	//_cube3->draw();
	//sprite->draw();
	//_heavy->draw();
	_sammich->draw();

	//_font->render();
}