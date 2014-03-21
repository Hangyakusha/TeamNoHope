#include <cmath>
#include <Engine.h>
#include <GameDemo.h>
#include <Windows.h>
#include <Mesh.h>
#include <iostream>
#include <Game.h>

using namespace NoHope;


Game::Game(float _desiredWidth,float _desiredHeight,float width,float height)
{
	desiredWidth = _desiredWidth;
	desiredHeight = _desiredHeight;

	Engine::deviceManager->FixAspectRatio(desiredWidth,desiredHeight,width,height);
	Init();
}

Game::~Game()
{
	delete gamedemo;
}

void Game::Init()
{
	gamedemo = new GameDemo(desiredWidth, desiredHeight);
	/*CreateObjects();*/
}
void Game::LoadContent()
{
	/*Engine::LoadContent();*/
}
void Game::Update(float dt)
{
	gamedemo->Update(dt);

}
void Game::Draw() //Draw
{
    //Draw 
    glClearColor(0.2f,0.2f,0.2f,1); 
    #ifndef ANDROID_FRAMEWORK 
    glClearDepth(1); 
    #else 
    glClearDepthf(1); 
    #endif 
  
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	
	gamedemo->Draw();
}

void Game::OnExit()
{
}

void Game::CreateObjects()
{
	float blackBarH, blackBarV, w,h;
	blackBarH = Engine::deviceManager->blackBarH;
	blackBarV = Engine::deviceManager->blackBarV;
	w = Engine::deviceManager->w;
	h = Engine::deviceManager->h;

	glViewport((int)blackBarH, (int)blackBarV,(int)w,(int)h); // Sets up the OpenGL viewport
	
	//make the shader program; 
	//shader = new Shader();
	//GLuint Program = shader->createShader("Shaders\\shad.frag","Shaders\\shad.vert");
	//delete shader;
	GameDemo* gamedemo = new GameDemo(desiredWidth, desiredHeight);
}