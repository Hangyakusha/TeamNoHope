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
	dirX = 0;
	dirY = 0;
}

GameDemo::~GameDemo(void)
{
}

// PUBLIC

void GameDemo::Update(float dt)
{	
	Movement();
	Collision();
}

void GameDemo::Draw()
{
	bg->Draw();
	player->Draw();
	obstacle->Draw();
}

void GameDemo::SetProjection()
{
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glViewport(0,0,desiredWidth, desiredHeight);
	//glFrustum(0,desiredWidth,0,desiredHeight,-1,1);
	bg->SetProjection(desiredWidth, desiredHeight);
}

// PRIVATE

void GameDemo::Initialize()
{
	sceneShader = new Shader();
	GLuint Program = sceneShader->CreateShader("GameDemo.frag","GameDemo.vert");
	delete sceneShader;

	 //BackGround
	bg = new Quad(desiredWidth, desiredHeight, 0.6f, desiredWidth, desiredHeight);
	bg->SetProgram(Program);
	bg->SetTexture("Test.tga");

	// Player
	player = new Quad(desiredWidth,desiredHeight, 0.0f, 64, 64);
	player->SetProgram(Program);
	player->SetTexture("Test.tga");
	player->Move(100,100,0);

	//Obstacle for Collision
	obstacle = new Quad(desiredWidth, desiredHeight, 0.0f, 64, 64);
	obstacle->SetProgram(Program);
	obstacle->SetTexture("Obstacle.tga");
	obstacle->Move(1000,1000,0);
}

void GameDemo::Movement()
{

	//hiirtä ei vielä huomioida.
	nextX = player->GetPositionX(CurX)+dirX;
	nextY = player->GetPositionY(CurY)+dirY;

	//Left
	if(Input::isKeyDown(Key::A))
	{
		dirX=-10;
		dirY= 0;
		player->Move(nextX,nextY,0);

			if(Input::isKeyDown(Key::W))
			{
				dirX= 10;
				dirY= 10;
			}

			else if(Input::isKeyDown(Key::S))
			{
				dirX= 10;
				dirY= -10;	
			}
	}

	//Right
	else if(Input::isKeyDown(Key::D))
	{
		dirX= 10;
		dirY= 0;
		player->Move(nextX,nextY,0);

			if(Input::isKeyDown(Key::W))
			{
				dirX= 10;
				dirY= 10;
			}

			else if(Input::isKeyDown(Key::S))
			{
				dirX= 10;
				dirY= -10;	
			}
	}

	//Up
	else if(Input::isKeyDown(Key::W))
	{
		dirY= 10;
		dirX= 0;
		player->Move(nextX,nextY,0);

			if(Input::isKeyDown(Key::A))
			{
				dirX= -10;
				dirY= 10;
			}

			else if(Input::isKeyDown(Key::D))
			{
				dirX= 10;
				dirY= 10;	
			}
	}

	//Down
	else if(Input::isKeyDown(Key::S))
	{
		dirY=-10;
		dirX= 0;
		player->Move(nextX,nextY,0);
		
			if(Input::isKeyDown(Key::A))
			{
				dirX= -10;
				dirY= -10;
			}

			else if(Input::isKeyDown(Key::D))
			{
				dirX= 10;
				dirY= -10;	
			}
	}
}

void GameDemo::Collision()
{
	if(player->GetPositionX(CurX) == obstacle->GetPositionX(CurX))
	{
		printf("Pelaaja X: %d ", player->GetPositionX(CurX), "Obstaakkeli X: %d ", obstacle->GetPositionX(CurX));
		dirX=0;

	}

	if(player->GetPositionY(CurY) == obstacle->GetPositionY(CurY))
	{
		printf("Pelaaja Y: %d ", player->GetPositionY(CurY), "Obstaakkeli Y: %d ", obstacle->GetPositionX(CurY));
		dirY=0;
	}
	
	
}