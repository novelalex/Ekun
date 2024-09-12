//
// Created by novel on 2024-09-10.
//

#include "Script.h"
#include <mruby/hash.h>
#include <mruby/array.h>
#include <mruby/compile.h>
#include "../core/Ekun.h"

using namespace MRB;

Script::Script() = default;

Script::Script(mrb_state *mrb, const std::string& filename) {
    LoadScript(mrb, filename);
    CreateArgs(mrb);

}

void Script::CreateArgs(mrb_state *mrb) {
    // This will be the main interface between the ruby scripts and the engine
    args = mrb_hash_new(mrb);

    // All assets will be loaded based on this
    load = mrb_hash_new(mrb);
    mrb_hash_set(mrb, load, MRuby::SymbolValue(mrb, EKRB_H_SPRITE), mrb_hash_new(mrb));
    mrb_hash_set(mrb, load, MRuby::SymbolValue(mrb, EKRB_H_FONT), mrb_hash_new(mrb));
    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb, EKRB_H_LOAD), load);

    // Any commands coming out of ruby and into the engine goes here (rendering, playing sounds, ...)
    output = mrb_ary_new(mrb);
    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb, EKRB_A_OUT), output);

    // Any data that the engine sends to the scripts will be accessed here (events, delta time, fps, screen size, ...)
    input = mrb_hash_new(mrb);

    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb, EKRB_H_IN), input);

    // This will not be touched by the engine
    state = mrb_hash_new(mrb);
    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb, EKRB_H_STATE), state);

    config = mrb_hash_new(mrb);
    mrb_hash_set(mrb, args, MRuby::SymbolValue(mrb, EKRB_H_CONFIG), config);
}

void Script::LoadScript(mrb_state *mrb, const std::string& filename) {
    std::string source = MRuby::readFile(filename) ;

    int ai = mrb_gc_arena_save(mrb);
    mrb_load_string(mrb, source.c_str());
    mrb_gc_arena_restore(mrb, ai);
    RB_EXC;
}
