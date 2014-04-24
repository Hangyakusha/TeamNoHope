#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <GameObject.h>
#include <Rigidbody.h>

namespace NoHope
{
	class Player : public GameObject
	{
	public:
		Player(int x, int y, int width, int height, Texture *texture, Shader *shader, b2World* world);
		~Player();
		//void Init(Vec2 position, float angle, Vec2 size);
		//Rigidbody *rigidbody; valmiiksi gameobjectissa
		void update(float dt);
		bool isJumping;
		int jumpTimeout;
		Vec2 mov;
		//bool playerDirection;

	private:
		void movement(float dt);
		void jumping(float dt);
	};
}


#endif