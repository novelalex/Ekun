//
// Created by novel on 2024-09-10.
//

#include "Sprite.h"

#include <iostream>
#include <ostream>
#include <utility>

Sprite::Sprite(): texture{nullptr} {

}

Sprite::Sprite(const std::string& filename, SDL_Renderer* renderer) {
    texture = loadTexture(filename, renderer);
    if (texture == nullptr) {
        std::cout << "Failed to load texture: " << filename <<std::endl;
    }
}

Sprite::~Sprite() {
    //std::cout << "Destroying Sprite" << std::endl;
    SDL_DestroyTexture(texture);
}

SDL_Texture * Sprite::getTexture() {
    return texture;
}

void Sprite::Draw(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

SDL_Texture* Sprite::loadTexture( std::string path, SDL_Renderer* renderer ) {
    //The final texture
    SDL_Texture* newTexture = nullptr;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}
