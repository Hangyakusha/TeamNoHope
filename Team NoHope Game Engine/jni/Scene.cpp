#include "Scene.h"
#include "Debug.h"
#include "Util.h"

using namespace gg;

Scene::Scene()
{
	_shader = new Shader(Util::resourcePath + "Shaders/basic.vert", Util::resourcePath +  "Shaders/basic.frag");
}

Scene::~Scene()
{
	delete _shader;
}