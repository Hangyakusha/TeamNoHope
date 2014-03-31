#ifndef FONT_H
#define FONT_H

#include "Entity.h"
#include "Shader.h"
#include "Texture.h"
#include "spriteEntity.h"
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace gg
{
    class Font : public Entity
    {
    public:
        
		Font();
		~Font();

		void load(const std::string& fontName, Shader* shader);
		void render();
		virtual void update(float dt);
		virtual void draw(); 

		static FT_Library library;
		static void initFontLibrary();
        
    private:
       
		FT_Face fontFace;
		Texture* texture;
		SpriteEntity* text;

    };
}
#endif