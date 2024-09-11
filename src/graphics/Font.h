//
// Created by novel on 2024-09-11.
//

#ifndef EKUN_FONT_H
#define EKUN_FONT_H


#include <string>
#include "SDL_ttf.h"

class Font {
private:
    TTF_Font* font {nullptr};

public:
    TTF_Font* GetFont() const;

public:
    Font(const char* filename, int fontsize);
    ~Font();

};
#endif //EKUN_FONT_H
