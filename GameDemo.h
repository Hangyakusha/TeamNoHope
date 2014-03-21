#pragma once

#ifndef GAMEDEMO_H
#define GAMEDEMO_H

#include <Quad.h>
#include <Shader.h>

namespace NoHope
{
	class GameDemo
	{
	public:
		GameDemo(float w, float h);
		~GameDemo(void);

		void Update(float dt);
		void Draw();
		void SetProjection();
		void Movement();

	private:

		void Initialize();

		Quad* player;

		float desiredWidth;
		float desiredHeight;

		Shader* sceneShader;
	};
}
#endif