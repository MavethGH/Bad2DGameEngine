#pragma once

#include <freetype/freetype.h>
#include <string>
#include <unordered_map>
#include "Texture.h"

struct FontCharacter
{
    Texture* glyphTex;

    struct {
        int x;
        int y;
    } bearing;

    int advance;
};

class FontManager
{
public:
    static void renderText(const std::string& text);

private:
    static std::unordered_map<char, FontCharacter> arialMap;
    static void loadArialGlyphs();
};