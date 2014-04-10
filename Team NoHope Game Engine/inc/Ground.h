#pragma once
#include "GameObject.h"
namespace NoHope
{
class Ground :
	public GameObject
{
public:
	Ground(int x, int y, int width, int height, Texture *texture, Shader *shader, b2World* world);
	~Ground();
};
}
