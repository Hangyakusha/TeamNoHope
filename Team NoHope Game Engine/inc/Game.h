#pragma once

#ifndef GAME_H
#define GAME_H

#include "Graphics.h"
#include "SpriteEntity.h"
#include "Shader.h"
#include "RenderTexture.h"
#include <vector>
#include "math/Vec2.h"
#include "math/Mat4.h"
//#include "Scene.h"
//#include "Sound.h"
#include "Mesh.h"
//#include "Font.h"
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "Text.h"
#include "Camera.h"

class Game
{

public:

	Game(int width, int height);
	~Game();

	void init();
	void update(float dt);
	void render();
	void addSprite(int x, int y, int dirX, int dirY);

	

	struct Sprite
	{
		NoHope::SpriteEntity* entity;
		NoHope::Vec2 direction;
		float speed;
	};

private:

	std::vector<Sprite> sprites;
	NoHope::Texture* texture;
	NoHope::RenderTexture* renderTexture;
	NoHope::SpriteEntity* sprite;
	NoHope::Graphics *_graphics;
	NoHope::Shader *_shader;
	NoHope::Mat4 _projection;
	NoHope::Mat4 _projection3D;
	//NoHope::Sound* _sound;
	//NoHope::Sound* _sound2;

	//NoHope::Font* _font;


	NoHope::Texture *_player;
	NoHope::GameObject *player;

	NoHope::Texture *_enemy;
	NoHope::GameObject *enemy;

	NoHope::Texture *_ground;
	NoHope::GameObject *ground;

	NoHope::Texture *_ground2;
	NoHope::GameObject *ground2;

	NoHope::Texture *_ground3;
	NoHope::GameObject *ground3;

	NoHope::Texture *_ground4;
	NoHope::GameObject *ground4;

	NoHope::Texture *_sky;
	NoHope::GameObject *sky;

	NoHope::Text *text;
	NoHope::SpriteEntity *bg;
	
	NoHope::Camera _camera;
	b2World world;


	float _timer;
	float fpsTimer;
	int fps;
};

#endif