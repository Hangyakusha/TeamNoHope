#include <GameDemo.h>
#include <cmath>
#include <input.h>

#include <iostream>

using namespace NoHope;

GameDemo::GameDemo(float w, float h)
{
	desiredWidth = w;
	desiredHeight = h;
	Initialize();
	SetProjection();
}

GameDemo::~GameDemo(void)
{
}

// PUBLIC

void GameDemo::Update(float dt)
{	
	Movement();
}

void GameDemo::Draw()
{
	//bg->Draw();
	player->Draw();
}

void GameDemo::SetProjection()
{
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glViewport(0,0,desiredWidth, desiredHeight);
	//glFrustum(0,desiredWidth,0,desiredHeight,-1,1);
	player->SetProjection(desiredWidth, desiredHeight);
}

// PRIVATE

void GameDemo::Initialize()
{
	sceneShader = new Shader();
	GLuint Program = sceneShader->CreateShader("GameDemo.frag","GameDemo.vert");
	delete sceneShader;

	// BackGround
	//bg = new Quad(desiredWidth, desiredHeight, 0.6f, desiredWidth, desiredHeight);
	//bg->SetProgram(Program);
	//bg->SetTexture("Eti texture");

	// Player
	player = new Quad(desiredWidth,desiredHeight, 0.4f, 64, 64);
	player->SetProgram(Program);
	player->SetTexture("Test.tga");
}

void GameDemo::Movement()
{
	//hiirtä ei vielä huomioida.
	
	//Left
	if(Input::isKeyDown(Key::A))
	{
		player->Move(50,50,0);
	}

	if(Input::isKeyDown(Key::D))
	{
		player->Move(5,5,0);
	}

	if(Input::isKeyDown(Key::W))
	{
		player->Move(0.001,0,0);
	}

	if(Input::isKeyDown(Key::S))
	{
		player->Move(-0.001,0,0);
	}
}