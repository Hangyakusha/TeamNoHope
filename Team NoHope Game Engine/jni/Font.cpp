#include "Font.h"
#include "SpriteEntity.h"
#include "Debug.h"
#include "Texture.h"

using namespace gg;

FT_Library Font::library;

void Font::initFontLibrary()
{
	int error = FT_Init_FreeType(&Font::library);
	if (error)
	{
		writeLog("Error initializing fonts!");
	}
}

Font::Font() {}

Font::~Font() {}

void Font::load(const std::string& fontName, Shader* shader)
{
	int error = FT_New_Face(Font::library, fontName.c_str(), 0, &fontFace);
	if(error)
		writeLog("Error creating a font face");

	error = FT_Set_Char_Size(
            fontFace,    /* handle to face object           */
            0,       /* char_width in 1/64th of points  */
            16*64,   /* char_height in 1/64th of points */
            300,     /* horizontal device resolution    */
            300 );   /* vertical device resolution      */
	if(error)
		writeLog("Error adjusting font sizes");

	error = FT_Load_Char(fontFace, 'Q', FT_LOAD_RENDER);
	if(error)
		writeLog("Error rendering glyph");

	texture = new Texture(fontFace->glyph->bitmap.buffer, 
									fontFace->glyph->bitmap.width,
									fontFace->glyph->bitmap.rows,
									32);

	text = new SpriteEntity(100, 100, -fontFace->glyph->bitmap.width, 100, texture, shader);
}

void Font::render()
{
	text->draw();
}

void Font::update(float dt)
{

}

void Font::draw()
{

}