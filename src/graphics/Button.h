//
// Created by novel on 12/6/2024.
//

#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <string>
#include "Font.h"
#include "TextBox.h"

class Button {
public:
    Button(int x, int y, int w, int h, const std::string& text_);
    ~Button();

    void Draw(SDL_Renderer* renderer, Font* font);
    bool IsMouseOver(int mouseX, int mouseY) const;
    std::string text;


private:
    SDL_Rect rect;
    TextBox* textbox;
};



#endif //BUTTON_H
