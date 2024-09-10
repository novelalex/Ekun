//
// Created by novel on 2024-09-08.
//

#include "Game.h"
#include <mruby/compile.h>
#include <mruby/hash.h>
#include <mruby/array.h>

#include <iostream>

using namespace MRB;

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
    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb, "load"), load);

    // Any commands coming out of ruby and into the engine goes here (rendering, playing sounds, ...)
    output = mrb_ary_new(mrb);
    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb,"out"), output);

    // Any data that the engine sends to the scripts will be accessed here (events, delta time, fps, screen size, ...)
    input = mrb_hash_new(mrb);
    mrb_hash_set(mrb,input, MRuby::SymbolValue(mrb,"dt"), mrb_nil_value());
    mrb_hash_set(mrb,args, MRuby::SymbolValue(mrb,"in"), input);

    // This will not be touched by the engine
    state = mrb_hash_new(mrb);
    mrb_hash_set(mrb,args, MRuby::SymbolValue(mrb,"state"), state);

    config = mrb_hash_new(mrb);
    mrb_hash_set(mrb,args, MRuby::SymbolValue(mrb,"config"), config);
    return true;
}

void Game::OnDestroy() {
    //mrb_gc_unregister(mrb, args);
    mrb_close(mrb);
}

void Game::Init() {

    mrb_funcall(mrb, mrb_top_self(mrb), "init", 1, args);
    if(mrb->exc) {
        mrb_print_error(mrb);
        mrb_print_backtrace(mrb);
    }

}

void Game::HandleEvents(const SDL_Event &sdlEvent) {

}

void Game::Update(const float deltaTime) {
    rb dt = mrb_float_value(mrb, deltaTime);
    mrb_hash_set(mrb, input, MRuby::SymbolValue(mrb, "dt"), dt);
    //std::cout << MRuby::TypeString(args) << '\n';
    mrb_funcall(mrb, mrb_top_self(mrb), "update", 1, args);
    if(mrb->exc) {
        mrb_print_error(mrb);
        mrb_print_backtrace(mrb);
    }
}

void Game::Render() const {

    //std::cout << MRuby::TypeString(args) << '\n';
    mrb_funcall(mrb, mrb_top_self(mrb), "render", 1, args);
    if(mrb->exc) {
        mrb_print_error(mrb);
        mrb_print_backtrace(mrb);
    }

}

