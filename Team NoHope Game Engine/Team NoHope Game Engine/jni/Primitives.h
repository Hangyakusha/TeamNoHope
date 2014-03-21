#pragma once
#ifndef Primitives_H
#define Primitives_H

#include <ObjLoader.h>
#include <glm\glm.hpp>

#include <vector>
#include <string>

namespace NoHope
{
	
	class Primitives
	{
	public:
		struct Model
		{
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec2> uvs;
			std::vector<glm::vec3> normals;
		}; 

		Primitives();
		~Primitives();

		static struct Model Cube;
		static struct Model Plane;
		static struct Model Sphere;
		static struct Model Moon;
		static struct Model Dome;

	private:
		Primitives(const Primitives&);

		void Load(const char* _path);
		void Clear();

		ObjLoader* obj;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
	};
}
#endif