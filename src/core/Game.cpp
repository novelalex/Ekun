//
// Created by novel on 2024-09-08.
//

#include "Game.h"
#include "Ekun.h"
#include <mruby/compile.h>
#include <mruby/hash.h>
#include <mruby/array.h>

#include <iostream>
#include <mruby/string.h>
#include <mruby.h>
#include <string>
#include <mruby/variable.h>
#include <filesystem>
#include "Debug.h"

std::string g_lastException;

using namespace MRB;

Game::Game() {
}

Game::~Game() {
    OnDestroy();
}


bool Game::OnCreate() {
    mrb = mrb_open();
    script = Script(mrb, "script.rb");
    assets = Assets();

    return true;
}

void Game::OnDestroy() {
    //mrb_gc_unregister(mrb, args);

    for (const auto &kv: assets.sprites) {
        delete kv.second;
    }

    for (const auto &kv: assets.fonts) {
        delete kv.second;
    }

    mrb_close(mrb);
}

void Game::Init(SDL_Renderer *renderer) {
    mrb_funcall(mrb, mrb_top_self(mrb), EKRB_FN_ON_CREATE, 1, script.args);
    if (mrb->exc) {
        mrb_print_error(mrb);
        mrb_print_backtrace(mrb);
    }

    rb load_hash = mrb_hash_get(mrb, script.args, MRuby::SymbolValue(mrb, EKRB_H_LOAD));
    RB_EXC;
    LoadSprites(renderer, load_hash);
    LoadFonts(load_hash);
}

void Game::LoadSprites(SDL_Renderer *renderer, rb &load_hash) {
    rb sprite_hash = mrb_hash_get(mrb, load_hash, MRuby::SymbolValue(mrb, EKRB_H_SPRITE));
    RB_EXC;
    rb sprite_names = mrb_hash_keys(mrb, sprite_hash);
    RB_EXC;
    for (size_t i = 0; i < RARRAY_LEN(sprite_names); i++) {
        const char *sprite_path = mrb_str_to_cstr(
                mrb,
            mrb_hash_get(
                    mrb,
                sprite_hash,
                mrb_ary_entry(sprite_names, i))
        );
        RB_EXC;
        const char *sprite_name = mrb_str_to_cstr(
                mrb,
            mrb_funcall(mrb,
                        mrb_ary_entry(sprite_names, i),
                        EKRB_FN_TO_STRING,
                        0,
                        nullptr));
        RB_EXC;

        std::cout << "Loading: " << sprite_path << " into " << sprite_name << std::endl;
        assets.sprites[sprite_name] = new Sprite(sprite_path, renderer);
    }
}

void Game::LoadFonts(rb &load_hash) {
    rb font_hash = mrb_hash_get(mrb, load_hash, MRuby::SymbolValue(mrb, EKRB_H_FONT));
    RB_EXC;
    rb font_names = mrb_hash_keys(mrb, font_hash);
    RB_EXC;
    for (size_t i = 0; i < RARRAY_LEN(font_names); i++) {
        rb font_info = mrb_hash_get(
                        mrb,
                        font_hash,
                        mrb_ary_entry(font_names, i)
                        );
        const char* font_path = mrb_str_to_cstr(mrb, mrb_ary_entry(font_info, 0));
        RB_EXC;
        int font_size = mrb_integer(mrb_ary_entry(font_info, 1));
        RB_EXC;
        const char *font_name = mrb_str_to_cstr(
                mrb,
                mrb_funcall(mrb,
                            mrb_ary_entry(font_names, i),
                            EKRB_FN_TO_STRING,
                            0,
                            nullptr));
        RB_EXC;
        if(!std::filesystem::exists(font_path)) {
            std::string errString =  font_path;
            Debug::FatalError("FILE NOT FOUND: " + errString, __FILE__, __LINE__);
        }
        std::cout << "Loading: " << font_path << " into " << font_name << std::endl;
        TTF_Font* ttf =  TTF_OpenFont(font_path, font_size);
        if (ttf == nullptr) {
            std::cout << "WHY IT NO WORKY??" << std::endl;
        }
        assets.fonts[font_name] = new Font(font_path, font_size);
    }
}

void Game::reloadScript(SDL_Renderer *renderer) {
    OnDestroy();
    OnCreate();
    Init(renderer);
}

void Game::HandleEvents(SDL_Renderer *renderer, GameManager* manager) {
    SDL_Event sdlEvent;
        rb kb = mrb_int_value(mrb, SDL_SCANCODE_UNKNOWN);
    while (SDL_PollEvent(&sdlEvent)) {

        /// Loop over all events in the SDL queue
        if (sdlEvent.type == SDL_EventType::SDL_QUIT) {
            manager->isRunning = false;
            return;
        }
        if (sdlEvent.type == SDL_KEYDOWN) {
            switch (sdlEvent.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    manager->isRunning = false;
                    return;
                default: ;
            }
            //std::cout << "here" << std::endl;
            kb = mrb_int_value(mrb, sdlEvent.key.keysym.scancode);
        }
        if (manager->game == nullptr) { /// Just to be careful
            Debug::FatalError("No Game:", __FILE__, __LINE__);
            manager->isRunning = false;
            return;
        }
        mrb_hash_set(mrb, script.input, MRuby::SymbolValue(mrb, "keyboard"), kb);
        mrb_funcall(mrb, mrb_top_self(mrb), "handle_events", 1, script.args);

    }
}

void Game::Update(const float deltaTime) {
    rb dt = mrb_float_value(mrb, deltaTime);
    rb fps = mrb_float_value(mrb, 1.0f / deltaTime);
    mrb_hash_set(mrb, script.input, MRuby::SymbolValue(mrb, EKRB_F_DT), dt);
    mrb_hash_set(mrb, script.input, MRuby::SymbolValue(mrb, EKRB_F_FPS), fps);
    //std::cout << MRuby::TypeString(args) << '\n';
    mrb_funcall(mrb, mrb_top_self(mrb), EKRB_FN_UPDATE, 1, script.args);
    if (mrb->exc) {
        mrb_print_error(mrb);
        mrb_print_backtrace(mrb);
    }
}

void Game::Render(SDL_Renderer *renderer) {
    //std::cout << MRuby::TypeString(args) << '\n';
    script.output = mrb_ary_new(mrb);
    mrb_hash_set(mrb, script.args, MRuby::SymbolValue(mrb, EKRB_A_OUT), script.output);

    mrb_funcall(mrb, mrb_top_self(mrb), EKRB_FN_RENDER, 1, script.args);
    if (mrb->exc) {
        mrb_print_error(mrb);
        mrb_print_backtrace(mrb);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderClear(renderer);
    rb out_commands = mrb_hash_get(mrb, script.args, MRuby::SymbolValue(mrb, EKRB_A_OUT)); RB_EXC;
    HandleOutputs(renderer, out_commands);

    SDL_RenderPresent(renderer);
    CleanupTextures();
}

void Game::HandleOutputs(SDL_Renderer *renderer, rb &out_commands) {
    for (size_t i = 0; i < RARRAY_LEN(out_commands); i++) {
        //std::cout << RARRAY_LEN(out_commands) << std::endl;
        rb command = mrb_ary_entry(out_commands, i);RB_EXC;

        // HANDLE SPRITES
        size_t command_len = mrb_hash_size(mrb, command);
        if (MRuby::CheckHashKeyExist(mrb, command, EKRB_H_SPRITE)) {
            if (command_len == 5) RenderSpriteDest(renderer, command);
            else if (command_len == 2) RenderSpriteDestRect(renderer, command);
        } else if (MRuby::CheckHashKeyExist(mrb, command, EKRB_H_FONT)) {
            if (command_len == 5) RenderFont(renderer, command);
            else if (command_len == 6) RenderFontWidth(renderer, command);

        }

    }
}

void Game::RenderSpriteDest(SDL_Renderer *renderer, rb &command) {
    std::string name = MRuby::GetHashValueString(mrb, command, EKRB_H_SPRITE);
    SDL_Rect texture_rect;
    texture_rect.x = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, "x"));
    texture_rect.y = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, "y"));
    texture_rect.w = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, "w"));
    texture_rect.h = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, "h"));

    Sprite *s = assets.sprites.at(name);
    SDL_RenderCopy(renderer, s->getTexture(), nullptr, &texture_rect);
}


void Game::RenderSpriteDestRect(SDL_Renderer *renderer, rb command) {
    std::string name = MRuby::GetHashValueString(mrb, command, EKRB_H_SPRITE);
    SDL_Rect texture_rect;
    rb dest_arry = mrb_hash_get(mrb, command, MRuby::SymbolValue(mrb, "dest"));
    texture_rect.x = mrb_int(mrb, mrb_ary_entry(dest_arry, 0));
    texture_rect.y = mrb_int(mrb, mrb_ary_entry(dest_arry, 1));
    texture_rect.w = mrb_int(mrb, mrb_ary_entry(dest_arry, 2));
    texture_rect.h = mrb_int(mrb, mrb_ary_entry(dest_arry, 3));

    Sprite *s = assets.sprites.at(name);
    SDL_RenderCopy(renderer, s->getTexture(), nullptr, &texture_rect);
}

void Game::RenderFontWidth(SDL_Renderer *renderer, rb command) {
    std::string name = MRuby::GetHashValueString(mrb, command, EKRB_H_FONT);
    int x = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, EKRB_F_X));
    int y = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, EKRB_F_Y));
    int w = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, EKRB_F_W));
    rb color = mrb_hash_get(mrb, command, MRuby::SymbolValue(mrb, EKRB_A_COLOR));
    uint8_t r = mrb_int(mrb, mrb_ary_entry(color, 0));
    uint8_t g = mrb_int(mrb, mrb_ary_entry(color, 1));
    uint8_t b = mrb_int(mrb, mrb_ary_entry(color, 2));
    uint8_t a = mrb_int(mrb, mrb_ary_entry(color, 3));
    SDL_Color font_color = {r,g,b,a};

    Font* f = assets.fonts.at(name);
    if (!f->GetFont()) {
        Debug::Error("Font not found: " + name, __FILE__, __LINE__);
        return;
    }

    const char* text = mrb_str_to_cstr(
            mrb,
            mrb_hash_get(
                    mrb,
                    command,
                    MRuby::SymbolValue(mrb, "text"))
    );

    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(f->GetFont(), text, font_color, w);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        Debug::Error("Failed to create texture: " + std::string(SDL_GetError()), __FILE__, __LINE__);
        SDL_FreeSurface(surface);
        return;
    }

    int text_width = surface->w;
    int text_height = surface->h;
    SDL_FreeSurface(surface);

    // Print debug information about the rendered text
    //Debug::Info("Rendered text dimensions: " + std::to_string(text_width) + "x" + std::to_string(text_height), __FILE__, __LINE__);

    // Render the texture
    SDL_Rect dest = {x , y , text_width, text_height};
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
    textures_to_destroy.push_back(texture);
}

void Game::RenderFont(SDL_Renderer *renderer, rb command) {
    std::string name = MRuby::GetHashValueString(mrb, command, EKRB_H_FONT);
    int x = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, EKRB_F_X));
    int y = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, EKRB_F_Y));
    rb color = mrb_hash_get(mrb, command, MRuby::SymbolValue(mrb, EKRB_A_COLOR));
    uint8_t r = mrb_int(mrb, mrb_ary_entry(color, 0));
    uint8_t g = mrb_int(mrb, mrb_ary_entry(color, 1));
    uint8_t b = mrb_int(mrb, mrb_ary_entry(color, 2));
    uint8_t a = mrb_int(mrb, mrb_ary_entry(color, 3));
    SDL_Color font_color = {r,g,b,a};

    Font* f = assets.fonts.at(name);
    if (!f->GetFont()) {
        Debug::Error("Font not found: " + name, __FILE__, __LINE__);
        return;
    }

    const char* text = mrb_str_to_cstr(
            mrb,
            mrb_hash_get(
                    mrb,
                    command,
                    MRuby::SymbolValue(mrb, "text"))
    );

    SDL_Surface* surface = TTF_RenderText_Blended(f->GetFont(), text, font_color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        Debug::Error("Failed to create texture: " + std::string(SDL_GetError()), __FILE__, __LINE__);
        SDL_FreeSurface(surface);
        return;
    }

    int text_width = surface->w;
    int text_height = surface->h;
    SDL_FreeSurface(surface);

    // Print debug information about the rendered text
    //Debug::Info("Rendered text dimensions: " + std::to_string(text_width) + "x" + std::to_string(text_height), __FILE__, __LINE__);

    // Render the texture
    SDL_Rect dest = {x , y , text_width, text_height};
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
    textures_to_destroy.push_back(texture);
}
void Game::CleanupTextures() {
    for (auto texture : textures_to_destroy) {
        SDL_DestroyTexture(texture);
    }
    textures_to_destroy.clear();
}


