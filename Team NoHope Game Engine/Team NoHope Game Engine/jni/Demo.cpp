#include <Demo.h>
#include <Util.h>
#include <Camera.h>

using namespace NoHope;

Demo::Demo(float w, float h)
{
	desiredWidth = w;
	desiredHeight = h;
	CreateScenes();

	activeScene = 1;
	sceneTimer = 0.0f;

	keyPressed = false;
}

Demo::~Demo(void)
{
	delete _primitives;

	delete scene1;
	delete scene2;
	//delete scene3;
	//delete scene4;
	//delete scene5;
	//delete scene6;
}

// PUBLIC
void Demo::Update(float dt)
{
	if(activeScene == 4)
		sceneTimer += dt/2.1f;
	else if(activeScene == 5)
		sceneTimer += dt/2.5f;
	else
		sceneTimer += dt;

	if(sceneTimer > 0.01f)
	{
		sceneTimer = 0.0f;
		if(activeScene < 2)
			activeScene++;
		else
			activeScene = 1;
	}


	switch(activeScene)
	{
	case 1:
		scene1->SetProjection();
		scene1->Update(dt);
		break;
	case 2:
		scene2->SetProjection();
		scene2->Update(dt);
		break;
	//case 3:
	//	scene3->SetProjection();
	//	scene3->Update(dt);
	//	break;
	//case 4:
	//	Scene05::resetCamera = false;
	//	scene4->SetProjection();
	//	scene4->Update(dt);
	//	break;
	//case 5:
	//	scene5->SetProjection();
	//	scene5->Update(dt);
	//	break;
	//case 6:
	//	Scene05::resetCamera = false;
	//	scene6->SetProjection();
	//	scene6->Update(dt);
	//	break;
	}
	
	if(GetAsyncKeyState(VK_SPACE) && !keyPressed)
		bgMusic->Pause();
	
	if(GetAsyncKeyState(VK_UP) && !keyPressed)
	{
		sceneTimer = 0.0f;
		if(activeScene < 2)
			activeScene++;
		else
			activeScene = 1;
	}
	if(GetAsyncKeyState(VK_DOWN) && !keyPressed)
	{
		sceneTimer = 0.0f;
		if(activeScene > 1)
			activeScene--;
		else
			activeScene = 2;
	}
	if(GetAsyncKeyState(VK_RIGHT) && !keyPressed)
		soundEffect[0]->PlayEffect();
	if(GetAsyncKeyState(VK_LEFT) && !keyPressed)
		soundEffect[1]->PlayEffect();
		
	
	keyPressed = GetAsyncKeyState(VK_SPACE) | GetAsyncKeyState(VK_UP) 
		| GetAsyncKeyState(VK_RIGHT) | GetAsyncKeyState(VK_LEFT) | GetAsyncKeyState(VK_DOWN);
}

void Demo::Draw()
{
	switch(activeScene)
	{
	case 1:
		scene1->Draw();
		break;
	case 2:
		scene2->Draw();
		break;
	//case 3:
	//	scene3->Draw();
	//	break;
	//case 4:
	//	scene4->Draw();
	//	break;
	//case 5:
	//	scene5->Draw();
	//	break;
	//case 6:
	//	scene6->Draw();
	//	break;
	}
}


// PRIVATE

void Demo::CreateScenes()
{
	_primitives = new Primitives();
	camera = Camera::CreateCamera(glm::vec3(0,10,30), glm::vec3(0,0,0), glm::vec3(0,1,0));

	bgMusic = Sound::Load(Util::resourcePath + "media/testi2.ogg");
	bgMusic->Loop(AL_TRUE);
	soundEffect[0] = Sound::Load(Util::resourcePath + "media/hit.ogg");
	//soundEffect[0]->Loop(AL_FALSE);
	soundEffect[1] = Sound::Load(Util::resourcePath + "media/ruby.ogg");
	//soundEffect[1]->Loop(AL_FALSE);
	
	scene1 = new Scene01(desiredWidth, desiredHeight);
	scene2 = new Scene02(desiredWidth, desiredHeight);
	//scene3 = new Scene03(desiredWidth, desiredHeight);
	//scene4 = new Scene04(desiredWidth, desiredHeight);
	//scene5 = new Scene05(desiredWidth, desiredHeight);
	//scene6 = new Scene06(desiredWidth, desiredHeight);

	bgMusic->Play(0);
}