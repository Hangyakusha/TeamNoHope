#include "RenderTexture.h"
#include "Debug.h"
#include "Util.h"
#include "Graphics.h"
#include <vector>

using namespace NoHope;

RenderTexture::RenderTexture():
	_bound(false)
{
	init();
}

RenderTexture::~RenderTexture() 
{
	glDeleteFramebuffers(1, &_frameBufferId);
	glDeleteRenderbuffers(1, &_depthBufferId);
}

void RenderTexture::init()
{
	std::vector<GLfloat> data(24);

	//vertex positions
	data[0] = -1.0f; data[1] = 1.0f;
	data[2] = -1.0f; data[3] = -1.0f;
	data[4] = 1.0f; data[5] = 1.0f;
	data[6] = 1.0f; data[7] = 1.0f;
	data[8] = -1.0f; data[9] = -1.0f;
	data[10] = 1.0f; data[11] = -1.0f;

	//texture coordinates
	data[12] = 0.0f; data[13] = 1.0f;
	data[14] = 0.0f; data[15] = 0.0f;
	data[16] = 1.0f; data[17] = 1.0f;
	data[18] = 1.0f; data[19] = 1.0f;
	data[20] = 0.0f; data[21] = 0.0f;
	data[22] = 1.0f; data[23] = 0.0f;

	_vertexData = new VertexData(data);

	//Create color attachment
	glGenFramebuffers(1, &_frameBufferId);
	checkGlError("glGenFramebuffers");

	_texture = new Texture(0, Graphics::screenWidth, 
								Graphics::screenHeight, 32);

	glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferId);
	checkGlError("glBindFramebuffer");

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture->getTextureObject(), 0);
	checkGlError("glFramebufferTexture2D");

	//Create depth attachment
	glGenRenderbuffers(1, &_depthBufferId);
	checkGlError("glGenRenderBuffers");

	glBindRenderbuffer(GL_RENDERBUFFER, _depthBufferId);
	checkGlError("glBindRenderbuffer");

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, Graphics::screenWidth, Graphics::screenHeight);
	checkGlError("glRenderbufferStorage");

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBufferId);
	checkGlError("glFramebufferRenderbuffer");

	////Create stencil attachment
	//glGenRenderbuffers(1, &_stencilBufferId);
	//checkGlError("glGenRenderBuffers");

	//glBindRenderbuffer(GL_RENDERBUFFER, _stencilBufferId);
	//checkGlError("glBindRenderbuffer");

	//glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, Graphics::screenWidth, Graphics::screenHeight);
	//checkGlError("glRenderbufferStorage");

	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _stencilBufferId);
	//checkGlError("glFramebufferRenderbuffer");

	//Check for completeness
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE)
		writeLog("\nFramebuffer is not complete!");
	else
		writeLog("\nFramebuffer is complete!");

	_shader = new Shader(Util::resourcePath + "Shaders/postprocess.vert", 
							Util::resourcePath + "Shaders/postprocessblank.frag");

	clear(Color(0, 0, 0));
}

void RenderTexture::draw(Entity& entity, Camera &_camera)
{
	bind();
	entity.draw(_camera);

	/*_data.insert(_data.end(), entity._vertexData->getData().begin(), entity._vertexData->getData().end());
	_batchTexture = entity._texture;
	_batchShader = entity._shader;*/
}

void RenderTexture::display()
{
	//_batchTexture->bind(_batchShader);
	//glUseProgram(_batchShader->program());

	//_batchData = new VertexData(_data);

	//static const int stride = sizeof(GLfloat)*8;

	//_batchData->bindBuffers();
	//_batchData->setAttribute(glGetAttribLocation(_batchShader->program(), "position"), 2, stride, 0); //vertex positions
	//_batchData->setAttribute(glGetAttribLocation(_batchShader->program(), "color"), 4, stride, sizeof(GLfloat)*2); //color
	//_batchData->setAttribute(glGetAttribLocation(_batchShader->program(), "texCoords"), 2, stride, sizeof(GLfloat)*6); //texture coordinates

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 500);

	//delete _batchData;
	//_data.clear();
	//_batchTexture = 0;
	//_batchShader = 0;

	unBind();

	glUseProgram(_shader->program());
	checkGlError("Glbaadadadad");

	_shader->setUniform("time", Util::getTotalTime());

	_texture->bind(_shader);
	_vertexData->bindBuffers();
	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "position"), 2, 0, 0);
	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "texCoords"), 2, 0, sizeof(GLfloat)*12);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	checkGlError("glDrawArraysframebuffer");
}

void RenderTexture::clear(const Color& color)
{
	bind();
	glClearColor(color.red, color.green, color.blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	checkGlError("Framebuffer clear");
	unBind();
}

void RenderTexture::bind()
{
	if(!_bound)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferId);
		checkGlError("glBindFramebuffers");
		_bound = true;
	}
}

void RenderTexture::unBind()
{
	if(_bound)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		checkGlError("glBindFramebuffer");
		_bound = false;
	}
}
