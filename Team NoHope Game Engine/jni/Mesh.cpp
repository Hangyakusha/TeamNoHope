#include "Mesh.h"
#include "math/Mat4.h"
#include "Debug.h"
#include "Graphics.h"
#include "ObjLoader.h"
#include "util.h"

//#include "Window.h"

using namespace gg;

Mesh::Mesh(Shader* shader, std::string filePath, Texture* texture):
	_shader(shader),
	_texture(texture)
{
	init(filePath);
}

Mesh::~Mesh()
{
}

void Mesh::init(std::string filePath)
{
	_camera = new Camera();

	std::vector<Vec3> vertices;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	std::vector<GLushort> indices;

	ObjLoader obj;
	obj.loadOBJ(filePath.c_str(), vertices, uvs, normals, indices);

	size = vertices.size();//indices.size();

	//this->setPosition(5, 0, 0);
	_camera->setPosition(0, 0, -10);

	std::vector<GLfloat> data(vertices.size()*sizeof(GLfloat)*8);

	int j = 0;
	for(int i = 0; i < vertices.size(); i++)
	{
		data[j] = vertices[i].x;
		data[j+1] = vertices[i].y;
		data[j+2] = vertices[i].z;

		data[j+3] = uvs[i].x;
		data[j+4] = uvs[i].y;

		data[j+5] = normals[i].x;
		data[j+6] = normals[i].y;
		data[j+7] = normals[i].z;
		j = j+8;
	}

	_vertexData = new VertexData(data);
	//_indexData = new IndexData(indices);
}

void Mesh::draw()
{
	//haxxing
	/*if(Window::getKey('A'))
		setRotationY(getRotation() + 0.1f);
	else if(Window::getKey('D'))
		setRotationY(getRotation() - 0.1f);
	if(Window::getKey('W'))
		setRotationX(getRotation() - 0.1f);
	else if(Window::getKey('S'))
		setRotationX(getRotation() + 0.1f);*/
	//if(Window::getKey(GLFW_KEY_D))
	//	_camera->setRotation(_camera->getRotation() + 0.1f);
	//	//_camera->setPosition(_camera->getPosition() + Vec3(-0.1f, 0, 0));
	//if(Window::getKey(GLFW_KEY_A))
	//	//_camera->setPosition(_camera->getPosition() + Vec3(0.1f, 0, 0));
	//	_camera->setRotation(_camera->getRotation() - 0.1f);
	//

	if(_texture)
		_texture->bind(_shader);

	glUseProgram(_shader->program());

	_shader->setUniform("view", _camera->getMatrix().data());
	_shader->setUniform("model", getMatrix().data());
	_shader->setUniform("projection", _projectionMatrix.data());

	//_indexData->bindBuffers();
	_vertexData->bindBuffers();

	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "position"), 3, sizeof(GLfloat)*8, 0);
	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "texCoords"), 2, sizeof(GLfloat)*8, sizeof(GLfloat)*3);

	//glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_SHORT, 0);
	glDrawArrays(GL_TRIANGLES, 0, size);
	checkGlError("glDrawElements");
}

void Mesh::update(float dt)
{
}