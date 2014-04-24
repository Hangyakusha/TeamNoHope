#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include <GameObject.h>


namespace NoHope
{
	class Enemy : public GameObject
	{
	public:
		Enemy(int x, int y, int width, int height, Texture *texture, Shader *shader, b2World* world);
		~Enemy();

		void update(float dt);
		bool isJumping;
		int jumpTimeout;
		Vec2 movs;
		//bool playerDirection;

	private:
		void movement(float dt);
		void jumping(float dt);

	};
}


#endif