#include "TextBox.h"


TextBox::TextBox() : surface{nullptr}, texture{nullptr}, rect{0, 0, 100, 100}, initial_width{100} {
}

TextBox::TextBox(int x, int y, int w, int h) : surface{nullptr}, texture{nullptr}, rect{x, y, w, h}, initial_width{w} {
}

TextBox::~TextBox() {
    Free();
}

void TextBox::Draw(SDL_Renderer *renderer, int x, int y) {
    rect.x = x;
    rect.y = y;
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void TextBox::Draw(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void TextBox::Update(const char *text, Font *font, SDL_Renderer *renderer) {
    Free();
    surface = TTF_RenderText_Blended_Wrapped(font->GetFont(), text, SDL_Color{255, 255, 255, 255}, initial_width);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    int text_width = surface->w;
    int text_height = surface->h;
    rect = {rect.x, rect.y, text_width, text_height};
}


void TextBox::Free() {
    if (surface != nullptr) {
        SDL_FreeSurface(surface);
    }

    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}
