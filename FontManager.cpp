#include "FontManager.h"
#include "Errors.h"
#include <SDL2/SDL_image.h>

std::unordered_map<char, FontCharacter> arialMap;

void FontManager::loadArialGlyphs()
{
    // Set up FreeType library to load font glyphs
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        fatalError("FreeType failed to initialize.");
    }
    FT_Face arial;
        if (FT_New_Face(ft, "../../arial.ttf", 0, &arial)) {
        fatalError("Could not load Arial font.");
    }

    // 16pt font size
    FT_Set_Char_Size(arial, 0, 16*64, 1024, 768);

    // First 128 ASCII characters
    for (unsigned char c = 0; c < 128; ++c) {
        if (FT_Load_Char(arial, c, FT_LOAD_RENDER)) {
            fatalError("Font machine broke.");
        }
        
        FontCharacter fontChar;
        fontChar.glyphTex = new Texture(&arial->glyph->bitmap);
        fontChar.bearing = {arial->glyph->bitmap_left, arial->glyph->bitmap_top};
        fontChar.advance = arial->glyph->advance.x;

        arialMap[c] = fontChar;
    }

    // Clean up FreeType's memory
    FT_Done_Face(arial);
    FT_Done_FreeType(ft);
}
