//
// Created by novel on 2024-09-11.
//

#include "Font.h"

Font::Font(const char *filename, int fontsize) {
    font = TTF_OpenFont(filename, fontsize);
}

Font::~Font() {
    TTF_CloseFont(font);
    font = nullptr;
}

TTF_Font *Font::GetFont() const {
    return font;
}
