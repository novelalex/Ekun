//
// Created by novel on 2024-09-08.
//

#include "Game.h"
#include <mruby/compile.h>
#include <mruby/hash.h>
#include <mruby/array.h>

#include <iostream>
#include <mruby/string.h>

using namespace MRB;

#define RB_EXC  if (mrb->exc) { mrb_print_error(mrb); mrb_print_backtrace(mrb);}

Game::Game(): mrb{nullptr}, args{}, game_instance{} {
}

Game::~Game() {
    OnDestroy();
}

bool Game::OnCreate() {
    mrb = mrb_open();
    std::string source = MRuby::readFile("script.rb");

    int ai = mrb_gc_arena_save(mrb);
    mrb_load_string(mrb, source.c_str());
    mrb_gc_arena_restore(mrb, ai);
    mrb_print_error(mrb);
    mrb_print_backtrace(mrb);


    // This will be the main interface between the ruby scripts and the engine
    args = mrb_hash_new(mrb);
    //mrb_gc_register(mrb, args);


    // All assets will be loaded based on this
    load = mrb_hash_new(mrb);
    mrb_hash_set(mrb, load, MRuby::SymbolValue(mrb, "sprite"), mrb_hash_new(mrb));
    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb, "load"), load);

    // Any commands coming out of ruby and into the engine goes here (rendering, playing sounds, ...)
    output = mrb_ary_new(mrb);
    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb, "out"), output);

    // Any data that the engine sends to the scripts will be accessed here (events, delta time, fps, screen size, ...)
    input = mrb_hash_new(mrb);
    mrb_hash_set(mrb, input, MRuby::SymbolValue(mrb, "dt"), mrb_nil_value());
    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb, "in"), input);

    // This will not be touched by the engine
    state = mrb_hash_new(mrb);
    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb, "state"), state);

    config = mrb_hash_new(mrb);
    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb, "config"), config);

    assets = Assets();

    return true;
}

void Game::OnDestroy() {
    //mrb_gc_unregister(mrb, args);
    std::vector<Sprite*> vals;
    vals.reserve(assets.sprites.size());

    for(const auto& kv : assets.sprites) {
        delete kv.second;
    }
    mrb_close(mrb);
}

void Game::Init(SDL_Renderer *renderer) {
    mrb_funcall(mrb, mrb_top_self(mrb), "on_create", 1, args);
    if (mrb->exc) {
        mrb_print_error(mrb);
        mrb_print_backtrace(mrb);
    }

    rb load_hash = mrb_hash_get(mrb, args, MRuby::SymbolValue(mrb, "load")); RB_EXC;
    rb sprite_hash = mrb_hash_get(mrb, load_hash, MRuby::SymbolValue(mrb, "sprite")); RB_EXC;
    rb sprite_names = mrb_hash_keys(mrb, sprite_hash); RB_EXC;
    for (size_t i = 0; i < RARRAY_LEN(sprite_names); i++) {
        const char *sprite_path = mrb_str_to_cstr(
            mrb,
            mrb_hash_get(
                mrb,
                sprite_hash,
                mrb_ary_entry(sprite_names, i))
        );RB_EXC;
        const char *sprite_name = mrb_str_to_cstr(
            mrb,
            mrb_funcall( mrb,
                mrb_ary_entry(sprite_names, i),
                "to_s",
                0,
                nullptr));RB_EXC;
        std::cout << "Loading: " << sprite_path << " into " << sprite_name << std::endl;
        assets.sprites[sprite_name] = new Sprite(sprite_path, renderer);
    }
}

void Game::HandleEvents(const SDL_Event &sdlEvent) {
}

void Game::Update(const float deltaTime) {
    rb dt = mrb_float_value(mrb, deltaTime);
    mrb_hash_set(mrb, input, MRuby::SymbolValue(mrb, "dt"), dt);
    //std::cout << MRuby::TypeString(args) << '\n';
    mrb_funcall(mrb, mrb_top_self(mrb), "update", 1, args);
    if (mrb->exc) {
        mrb_print_error(mrb);
        mrb_print_backtrace(mrb);
    }
}

void Game::Render(SDL_Renderer *renderer) {
    //std::cout << MRuby::TypeString(args) << '\n';
    output = mrb_ary_new(mrb);
    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb, "out"), output);

    mrb_funcall(mrb, mrb_top_self(mrb), "render", 1, args);
    if (mrb->exc) {
        mrb_print_error(mrb);
        mrb_print_backtrace(mrb);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderClear(renderer);
    rb out_commands = mrb_hash_get(mrb, args, MRuby::SymbolValue(mrb, "out")); RB_EXC;
    for (size_t i = 0; i < RARRAY_LEN(out_commands); i++) {
        //std::cout << RARRAY_LEN(out_commands) << std::endl;
        rb command = mrb_ary_entry(out_commands, i);
        std::string name = MRuby::GetHashValueString(mrb, command, "name");
        SDL_Rect texture_rect;
        texture_rect.x = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, "x"));
        texture_rect.y = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, "y"));
        texture_rect.w = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, "w"));
        texture_rect.h = static_cast<int>(MRuby::GetHashValueFloat(mrb, command, "h"));


        Sprite* s = assets.sprites.at(name);
        SDL_RenderCopy(renderer, s->getTexture(), nullptr, &texture_rect);
    }


    SDL_RenderPresent( renderer );

}
