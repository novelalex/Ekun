//
// Created by novel on 2024-09-08.
//

#include "Game.h"
#include "Ekun.h"
#include <mruby/compile.h>
#include <mruby/hash.h>
#include <mruby/array.h>
#include <mruby/gc.h>

#include <iostream>
#include <mruby/string.h>
#include <mruby.h>
#include <string>
#include <mruby/variable.h>
#include <filesystem>
#include "Debug.h"
#include "Window.h"

#define MRB_EXC if (mrb->exc) {mrb_print_error(mrb);}


using namespace MRB;

Game::Game() {
}

Game::~Game() {
    OnDestroy();
}


bool Game::OnCreate(GameManager *m) {
    mrb = mrb_open();
    script = Script(mrb, "script.rb");
    MRB_EXC
    assets = Assets();
    manager = m;
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
    if (mrb->exc) {
        mrb_print_error(mrb);
    }
    mrb_funcall(mrb, mrb_top_self(mrb), EKRB_FN_ON_CREATE, 1, script.args);
    if (mrb->exc) {
        mrb_print_error(mrb);
        mrb_print_backtrace(mrb);
    }
    window_info = mrb_hash_new(mrb);
    mouse_info = mrb_hash_new(mrb);
    rb load_hash = mrb_hash_get(mrb, script.args, MRuby::SymbolValue(mrb, EKRB_H_LOAD));
    MRB_EXC
    LoadSprites(renderer, load_hash);
    LoadFonts(load_hash);
}

void Game::LoadSprites(SDL_Renderer *renderer, rb &load_hash) {
    rb sprite_hash = mrb_hash_get(mrb, load_hash, MRuby::SymbolValue(mrb, EKRB_H_SPRITE));MRB_EXC
    rb sprite_names = mrb_hash_keys(mrb, sprite_hash);MRB_EXC
    for (size_t i = 0; i < RARRAY_LEN(sprite_names); i++) {
        const char *sprite_path = mrb_str_to_cstr(
                mrb,
                mrb_hash_get(
                        mrb,
                        sprite_hash,
                        mrb_ary_entry(sprite_names, i))
        );
        const char *sprite_name = mrb_str_to_cstr(
                mrb,
                mrb_funcall(mrb,
                            mrb_ary_entry(sprite_names, i),
                            EKRB_FN_TO_STRING,
                            0,
                            nullptr));

        std::cout << "Loading: " << sprite_path << " into " << sprite_name << std::endl;
        assets.sprites[sprite_name] = new Sprite(sprite_path, renderer);
        MRB_EXC
    }
}

void Game::LoadFonts(rb &load_hash) {
    rb font_hash = mrb_hash_get(mrb, load_hash, MRuby::SymbolValue(mrb, EKRB_H_FONT));MRB_EXC
    rb font_names = mrb_hash_keys(mrb, font_hash);MRB_EXC
    for (size_t i = 0; i < RARRAY_LEN(font_names); i++) {
        rb font_info = mrb_hash_get(
                mrb,
                font_hash,
                mrb_ary_entry(font_names, i)
        );
        const char *font_path = mrb_str_to_cstr(mrb, mrb_ary_entry(font_info, 0));
        int font_size = mrb_integer(mrb_ary_entry(font_info, 1));
        const char *font_name = mrb_str_to_cstr(
                mrb,
                mrb_funcall(mrb, mrb_ary_entry(font_names, i), EKRB_FN_TO_STRING, 0, nullptr));
        
        if (!std::filesystem::exists(font_path)) {
            std::string errString = font_path;
            Debug::FatalError("FILE NOT FOUND: " + errString, __FILE__, __LINE__);
        }
        std::cout << "Loading: " << font_path << " into " << font_name << std::endl;
        TTF_Font *ttf = TTF_OpenFont(font_path, font_size);
        if (ttf == nullptr) {
            std::cout << "WHY IT NO WORKY??" << std::endl;
        }
        assets.fonts[font_name] = new Font(font_path, font_size);
        MRB_EXC
    }

}

void Game::reloadScript(SDL_Renderer *renderer) {
    OnDestroy();
    OnCreate(manager);
    Init(renderer);
}

void Game::HandleEvents(SDL_Renderer *renderer) {
    int ai = mrb_gc_arena_save(mrb);

    SDL_Event sdlEvent;
    rb kb = mrb_int_value(mrb, SDL_SCANCODE_UNKNOWN);
    mrb_gc_arena_restore(mrb, ai);

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
                case SDL_SCANCODE_R:
                    reloadScript(renderer);
                default:;
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
        MRB_EXC
        mrb_funcall(mrb, mrb_top_self(mrb), "handle_events", 1, script.args);
        MRB_EXC
    }

}

void Game::Update(const float deltaTime) {
    int ai = mrb_gc_arena_save(mrb);

    rb dt = mrb_float_value(mrb, deltaTime);
    rb fps = mrb_float_value(mrb, 1.0f / deltaTime);
    mrb_gc_arena_restore(mrb, ai);
    MRB_EXC
    mrb_hash_set(mrb, window_info, MRuby::SymbolValue(mrb, "w"), mrb_int_value(mrb, manager->window->getWidth()));
    mrb_hash_set(mrb, window_info, MRuby::SymbolValue(mrb, "h"), mrb_int_value(mrb, manager->window->getHeight()));
    mrb_hash_set(mrb, script.input, MRuby::SymbolValue(mrb, "window"), window_info);
    MRB_EXC
    int x,y;
    SDL_GetMouseState(&x, &y);
    mrb_hash_set(mrb, mouse_info, MRuby::SymbolValue(mrb, "x"), mrb_int_value(mrb, x));
    mrb_hash_set(mrb, mouse_info, MRuby::SymbolValue(mrb, "y"), mrb_int_value(mrb, y));
    mrb_hash_set(mrb, script.input, MRuby::SymbolValue(mrb, "mouse"), mouse_info);
    MRB_EXC
    mrb_hash_set(mrb, script.input, MRuby::SymbolValue(mrb, EKRB_F_DT), dt);
    mrb_hash_set(mrb, script.input, MRuby::SymbolValue(mrb, EKRB_F_FPS), fps);
    MRB_EXC
    //std::cout << MRuby::TypeString(args) << '\n';
    mrb_funcall(mrb, mrb_top_self(mrb), EKRB_FN_UPDATE, 1, script.args);
    MRB_EXC


}

void Game::Render(SDL_Renderer *renderer) {
    int ai = mrb_gc_arena_save(mrb);

    //std::cout << MRuby::TypeString(args) << '\n';
    script.output = mrb_ary_new(mrb);
    mrb_hash_set(mrb, script.args, MRuby::SymbolValue(mrb, EKRB_A_OUT), script.output);

    mrb_funcall(mrb, mrb_top_self(mrb), EKRB_FN_RENDER, 1, script.args);
    if (mrb->exc) {
        mrb_print_error(mrb);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderClear(renderer);
    rb out_commands = mrb_hash_get(mrb, script.args, MRuby::SymbolValue(mrb, EKRB_A_OUT));
    HandleOutputs(renderer, out_commands);

    SDL_RenderPresent(renderer);
    CleanupTextures();
    mrb_gc_arena_restore(mrb, ai);


}

void Game::HandleOutputs(SDL_Renderer *renderer, rb &out_commands) {
    for (size_t i = 0; i < RARRAY_LEN(out_commands); i++) {
        //std::cout << RARRAY_LEN(out_commands) << std::endl;
        rb command = mrb_ary_entry(out_commands, i);
        

        // HANDLE SPRITES
        size_t command_len = mrb_hash_size(mrb, command);
        if (MRuby::CheckHashKeyExist(mrb, command, EKRB_H_SPRITE)) {
            RenderSprite(renderer, command);
        } else if (MRuby::CheckHashKeyExist(mrb, command, EKRB_H_FONT)) {
            RenderFont(renderer, command);
        }

    }
}

void Game::RenderSprite(SDL_Renderer *renderer, rb &command) {
    std::string name = MRuby::GetHashValueString(mrb, command, EKRB_H_SPRITE);

    SDL_Rect texture_rect{};

    if (MRuby::CheckHashKeyExist(mrb, command, EKRB_F_X) && MRuby::CheckHashKeyExist(mrb, command, EKRB_F_Y) &&
        MRuby::CheckHashKeyExist(mrb, command, EKRB_F_W) && MRuby::CheckHashKeyExist(mrb, command, EKRB_F_H)) {
        texture_rect.x = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, "x"));
        texture_rect.y = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, "y"));
        texture_rect.w = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, "w"));
        texture_rect.h = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, "h"));
    } else if (MRuby::CheckHashKeyExist(mrb, command, "dest")) {
        rb dest_arry = mrb_funcall(
                mrb,
                mrb_hash_get(mrb, command, MRuby::SymbolValue(mrb, "dest")),
                "to_a",
                0);
        texture_rect.x = mrb_int(mrb, mrb_ary_entry(dest_arry, 0));
        texture_rect.y = mrb_int(mrb, mrb_ary_entry(dest_arry, 1));
        texture_rect.w = mrb_int(mrb, mrb_ary_entry(dest_arry, 2));
        texture_rect.h = mrb_int(mrb, mrb_ary_entry(dest_arry, 3));
    } else {
        Sprite *s = assets.sprites.at(name);
        SDL_RenderCopy(renderer, s->getTexture(), nullptr, nullptr);
        return;
    }

    Sprite *s = assets.sprites.at(name);
    SDL_RenderCopy(renderer, s->getTexture(), nullptr, &texture_rect);
}

void Game::RenderFont(SDL_Renderer *renderer, rb command) {
    std::string name = MRuby::GetHashValueString(mrb, command, EKRB_H_FONT);
    int x = 0;
    int y = 0;
    if (MRuby::CheckHashKeyExist(mrb, command, EKRB_F_X) && MRuby::CheckHashKeyExist(mrb, command, EKRB_F_Y)) {
        x = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, EKRB_F_X));
        y = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, EKRB_F_Y));
    }
    SDL_Color font_color = {0, 0, 0, 255};
    if (MRuby::CheckHashKeyExist(mrb, command, EKRB_A_COLOR)) {
        rb color = mrb_hash_get(mrb, command, MRuby::SymbolValue(mrb, EKRB_A_COLOR));
        uint8_t r = mrb_int(mrb, mrb_ary_entry(color, 0));
        uint8_t g = mrb_int(mrb, mrb_ary_entry(color, 1));
        uint8_t b = mrb_int(mrb, mrb_ary_entry(color, 2));
        uint8_t a = mrb_int(mrb, mrb_ary_entry(color, 3));
        font_color = {r, g, b, a};
    }

    bool centered = false;
    if (MRuby::CheckHashKeyExist(mrb, command, EKRB_B_CENTERED)) {
        centered = mrb_bool(mrb_hash_get(mrb, command, MRuby::SymbolValue(mrb, EKRB_B_CENTERED)));
    }

    Font *f = assets.fonts.at(name);
    if (!f->GetFont()) {
        Debug::Error("Font not found: " + name, __FILE__, __LINE__);
        return;
    }
    const char *text = mrb_str_to_cstr(
            mrb,
            mrb_hash_get(mrb, command, MRuby::SymbolValue(mrb, "text"))
    );
    SDL_Surface *surface;

    if (MRuby::CheckHashKeyExist(mrb, command, EKRB_F_W)) {
        int w = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, EKRB_F_W));
        surface = TTF_RenderText_Blended_Wrapped(f->GetFont(), text, font_color, w);
    } else {
        surface = TTF_RenderText_Blended(f->GetFont(), text, font_color);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        Debug::Error("Failed to create texture: " + std::string(SDL_GetError()), __FILE__, __LINE__);
        SDL_FreeSurface(surface);
        return;
    }

    int text_width = surface->w;
    int text_height = surface->h;
    SDL_FreeSurface(surface);

    SDL_Rect dest{};
    if (centered) {
        dest = {x - text_width / 2, y - text_height / 2, text_width, text_height};
    } else {
        dest = {x, y, text_width, text_height};
    }
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
    textures_to_destroy.push_back(texture);
}

void Game::CleanupTextures() {
    for (auto texture: textures_to_destroy) {
        SDL_DestroyTexture(texture);
    }
    textures_to_destroy.clear();
}



