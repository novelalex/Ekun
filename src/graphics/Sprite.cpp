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
    std::cout << "Destroying Sprite" << std::endl;
    SDL_DestroyTexture(texture);
}

SDL_Texture * Sprite::getTexture() {
    return texture;
}

SDL_Texture* Sprite::loadTexture( std::string path, SDL_Renderer* renderer ) {
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}