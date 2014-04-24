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

Text::Text(std::string fontName, const float fontSize)
	:m_fontName(fontName),
	m_fontSize(fontSize)
{	
	GLubyte* fontData = Util::loadBinary(Util::resourcePath + "fonts/" + fontName,fontDataSize);

    m_atlas = texture_atlas_new( 1024, 1024, 1 );

	m_font = texture_font_new_from_memory( m_atlas, 16, fontData, fontDataSize);
	 //texture_font_delete( font );

	if (_shader == nullptr)
		_shader = new Shader(Util::resourcePath + "Shaders/v3f-t2f-c4f.vert", 
						Util::resourcePath +  "Shaders/v3f-t2f-c4f.frag");

	std::vector<float> startVertexes;
	startVertexes.push_back(.0f);
	_vertexData = new VertexData(startVertexes);

	std::vector<GLushort> startIndexes;
	startIndexes.push_back(0);
	_indexData = new IndexData(startIndexes,false);

	SetText(L"text Object");
}

Text::~Text()
{
	delete(m_atlas);
	delete(m_font);
}

void Text::SetText(const std::wstring& text, Vec4 color)
{
	m_text.clear();
	m_pos.clear();
	m_color.clear();
	m_texCoords.clear();
	m_indices.clear();
	pos = Vec2();
	//tekstin position
	AddText(text, color);
}

void Text::AddText(const std::wstring& text, Vec4 color)
{
	m_text += text;

	texture_font_load_glyphs(m_font, m_text.c_str());
	
	m_pos.reserve(m_text.size()*4);
	m_color.reserve(m_text.size()*4);
	m_texCoords.reserve(m_text.size()*4);

	m_indices.reserve(m_text.size()*6);

	bool newLine = false;

	for (size_t i = 0; i < text.length(); ++i)
	{
		texture_glyph_t* glyph = nullptr;
		if (text.at(i) == L'\n')
		{
			newLine = true;
			pos.y += m_fontSize;
			pos.x = 0;
		}
		else
			glyph = texture_font_get_glyph(m_font, text.at(i));

		if (glyph != nullptr)
		{
			float kerning = 0.f;
			if (i > 0 && !newLine)
				kerning = texture_glyph_get_kerning(glyph, text.at(i - 1));

			pos.x += kerning;
		
			const float x0 = pos.x + glyph->offset_x;
			const float y0 = pos.y - glyph->offset_y;
			const float x1 = x0 + glyph->width;
			const float y1 = y0 + glyph->height;

			const float s0 = glyph->s0; // Top left x
			const float t0 = glyph->t0; // Top left y
			const float s1 = glyph->s1; // Bottom right x
			const float t1 = glyph->t1; // Bottom right y
			
			m_pos.push_back(Vec2(x0, y0));
			m_pos.push_back(Vec2(x0, y1));
			m_pos.push_back(Vec2(x1, y1));
			m_pos.push_back(Vec2(x1, y0));
			
			m_color.push_back(color);
			m_color.push_back(color);
			m_color.push_back(color);
			m_color.push_back(color);
			
			m_texCoords.push_back(Vec2(s0, t0));
			m_texCoords.push_back(Vec2(s0, t1));
			m_texCoords.push_back(Vec2(s1, t1));
			m_texCoords.push_back(Vec2(s1, t0));

			const int lastIndex = (m_indices.size() / 6) * 4;
			m_indices.push_back(lastIndex + 0);
			m_indices.push_back(lastIndex + 1);
			m_indices.push_back(lastIndex + 2);
			m_indices.push_back(lastIndex + 0);
			m_indices.push_back(lastIndex + 2);
			m_indices.push_back(lastIndex + 3);

			pos.x += glyph->advance_x;
			newLine = false;
		}
	}

	_vertexData->SetNewData(m_pos,m_color,m_texCoords);
	_indexData->SetIndexes(m_indices);

		//const char *filename = "fonts/Vera.ttf";
		//const wchar_t *cache = L" !\"#$%&'()*+,-./0123456789:;<=>?"
		//                           L"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
		//                           L"`abcdefghijklmnopqrstuvwxyz{|}~";
		//printf( "Matched font               : %s\n", m_fontName.c_str() );
		//printf( "Number of glyphs per font  : %ld\n", wcslen(cache) );
		//printf( "Texture size               : %ldx%ld\n", m_atlas->width, m_atlas->height );
		//printf( "Texture occupancy          : %.2f%%\n", 
		//100.0*m_atlas->used/(float)(m_atlas->width*m_atlas->height) );

		//cache == text
		//glyphcount
		//mallii uth
		//vertex bufferit eri tavalla
		//indicet eri tavalla
		//draw() sattuu vielä
}


void Text::draw(Camera &_camera)
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

	_vertexData->bindBuffers();
	_indexData->bindBuffers();

	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "position"), 2, stride, 0); //vertex positions
	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "color"), 4, stride, sizeof(GLfloat)*2); //color
	_vertexData->setAttribute(glGetAttribLocation(_shader->program(), "texCoords"), 2, stride, sizeof(GLfloat)*6); //texture coordinates

	glDrawElements(GL_TRIANGLES, _indexData->getData().size()/* *letterCount  */, GL_UNSIGNED_SHORT, 0);
	
    checkGlError("glDrawText");
}