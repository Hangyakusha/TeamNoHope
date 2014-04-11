//#include <stdio.h>
//#include <wchar.h>
//
//#include "freetype-gl\freetype-gl.h"
//#include "freetype-gl\mat4.h"
//#include "freetype-gl\shader.h"
//#include "freetype-gl\vertex-buffer.h"
#include "Text.h"
//#include "math\Vec4.h"
//#include "math\Vec2.h"
#include "util.h"

using namespace NoHope;

NoHope::Shader* Text::_shader = nullptr;

Text::Text(std::string fontName)
	:m_fontName(fontName)
{	
	GLubyte* fontData = Util::loadBinary(Util::resourcePath + "fonts/" + fontName,fontDataSize);

     m_atlas = texture_atlas_new( 1024, 1024, 1 );

	m_font = texture_font_new_from_memory( m_atlas, 16, fontData, fontDataSize);
	 //texture_font_delete( font );

	if (_shader == nullptr)
		_shader = new Shader(Util::resourcePath + "Shaders/v3f-t2f-c4f.vert", 
						Util::resourcePath +  "Shaders/v3f-t2f-c4f.frag");
}

Text::~Text()
{
	delete(m_atlas);
	delete(m_font);
}

void Text::SetText(const std::wstring& text, Vec4 color)
{

	//tekstin position
	AddText(text, color);
}

void Text::AddText(const std::wstring& text, Vec4 color)
{
		//const char *filename = "fonts/Vera.ttf";
		const wchar_t *cache = L" !\"#$%&'()*+,-./0123456789:;<=>?"
		                           L"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
		                           L"`abcdefghijklmnopqrstuvwxyz{|}~";
		printf( "Matched font               : %s\n", m_fontName.c_str() );
		printf( "Number of glyphs per font  : %ld\n", wcslen(cache) );
		printf( "Texture size               : %ldx%ld\n", m_atlas->width, m_atlas->height );
		printf( "Texture occupancy          : %.2f%%\n", 
		100.0*m_atlas->used/(float)(m_atlas->width*m_atlas->height) );

		//cache == text
		//glyphcount
		//mallii uth
		//vertex bufferit eri tavalla
		//indicet eri tavalla
		//draw() sattuu vielä
}


void Text::draw()
{
	
	glUseProgram(_shader->program());

	glActiveTexture(GL_TEXTURE0);
	checkGlError("glACtiveTexture");

	glBindTexture(GL_TEXTURE_2D, m_atlas->id);
	checkGlError("glBindTextures");

	_shader->setUniform("vSampler", 0);

	_shader->setUniform("projection", _projectionMatrix.data());
	_shader->setUniform("model", getMatrix().data());
	
	static const int stride = sizeof(GLfloat)*8;

	//////////////////////// sattuu
	_vertexData->bindBuffers();
	_indexData->bindBuffers();
	////////////////////////

	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "position"), 2, stride, 0); //vertex positions
	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "color"), 4, stride, sizeof(GLfloat)*2); //color
	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "texCoords"), 2, stride, sizeof(GLfloat)*6); //texture coordinates

	glDrawElements(GL_TRIANGLES, 6/* *letterCount  */, GL_UNSIGNED_SHORT, 0);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    checkGlError("glDrawText");
}