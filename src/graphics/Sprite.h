//
// Created by novel on 2024-09-10.
//

#ifndef SPRITE_H
#define SPRITE_H


#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Sprite {
private:
    SDL_Texture* texture;

public:
    Sprite();

    Sprite(const std::string& filename, SDL_Renderer* renderer);
    ~Sprite();
    SDL_Texture* getTexture();

private:
    SDL_Surface *loadSurface(const std::string& path);

    SDL_Texture *loadTexture(std::string path, SDL_Renderer *renderer);
};


#endif //SPRITE_H