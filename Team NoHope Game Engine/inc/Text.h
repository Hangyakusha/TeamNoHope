#pragma once

#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <stdio.h>
#include <wchar.h>

#include "freetype\ft2build.h"
#include "freetype\freetype.h"
#include "freetype-gl\freetype-gl.h"
#include "freetype-gl\mat4.h"
#include "freetype-gl\shader.h"
#include "freetype-gl\vertex-buffer.h"
#include "freetype-gl\texture-font.h"
#include "Entity.h"
#include "Shader.h"
#include <VertexData.h>
#include <IndexData.h>
#include <string>


namespace NoHope
{
	class Text : public Entity
	{
	public:

		Text(std::string fontName, const float fontSize = 30.f);
		~Text();
		void SetText(const std::wstring& text, Vec4 color = Vec4(0, 0, 0, 1));
		void AddText(const std::wstring& text, Vec4 color = Vec4(0, 0, 0, 1));
		int fontDataSize;

		
		virtual void update(float dt){}
		virtual void draw(Camera &_camera);
		
	private:

		const float m_fontSize;

		std::wstring m_text;
		Vec2 pos;

		texture_font_t *m_font;
		texture_atlas_t *m_atlas;
		std::string m_fontName;
		static Shader* _shader;

		VertexData* _vertexData;
		IndexData* _indexData;

		std::vector<Vec2> m_pos;
		std::vector<Vec4> m_color;
		std::vector<Vec2> m_texCoords;

		std::vector<GLushort> m_indices;

	};
}

#endif