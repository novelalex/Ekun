//
// Created by novel on 12/6/2024.
//

#include "Button.h"

#include "../core/InputHandler.h"

Button::Button(int x, int y, int w, int h, const std::string& text_){
    rect = {x, y, w, h};
    textbox = new TextBox(x, y, w, h);
    text = text_;
}

Button::~Button() {
    delete textbox;
}

void Button::Draw(SDL_Renderer* renderer, Font* font) {
    SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

    textbox->Update(text.c_str(), font, renderer);
    textbox->Draw(renderer);

}

bool Button::IsMouseOver(int mouseX, int mouseY) const {
    return InputHandler::handle_click_zone(rect.x, rect.y, rect.w, rect.h, mouseX, mouseY);
}