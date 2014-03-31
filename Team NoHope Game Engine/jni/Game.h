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
#include "Sound.h"
#include "Mesh.h"
//#include "Font.h"

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
		gg::SpriteEntity* entity;
		gg::Vec2 direction;
		float speed;
	};

private:

	std::vector<Sprite> sprites;
	gg::Texture* texture;
	gg::RenderTexture* renderTexture;
	gg::SpriteEntity* sprite;
	gg::Graphics *_graphics;
	gg::Shader *_shader;
	gg::Mat4 _projection;
	gg::Mat4 _projection3D;
	gg::Sound* _sound;
	gg::Sound* _sound2;
	gg::Mesh* _cube;
	gg::Mesh* _cube2;
	gg::Mesh* _cube3;
	gg::Mesh* _heavy;
	gg::Mesh* _sammich;
	//gg::Font* _font;

	float _timer;
	int fps;
};

#endif