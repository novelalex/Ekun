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
#include "SaveSystem.h"
#include "StoryPlayer.h"


std::string read_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}


void Game::play_story(mrb_state* mrb, mrb_value story) {
    player = new StoryPlayer(mrb, story);
    player->play();
}

Game::Game(SDL_Renderer* r) : isRunning{ true }, renderer{r} {
}

Game::~Game() {
    OnDestroy();
}


bool Game::OnCreate() {
    font = new Font("fonts/Montserrat-Regular.ttf", 24);
    dialog_box = new TextBox(160, 450, 1000, 300);
    name_box = new TextBox(160, 400, 1000, 300);
    text_update_flag = true;
    return true;
}


void Game::OnDestroy() {
    delete dialog_box;
    delete name_box;
    delete player;
    delete font;
}

void Game::Init() {
    mrb = mrb_open();
    if (!mrb) {
        Debug::FatalError("Could not instantiate MRuby", __FILE__, __LINE__);
    }
    try {
        // Load the DSL definition
        std::string dsl_code = read_file("script.rb");
        mrb_load_string(mrb, dsl_code.c_str());

        // Load the story
        mrb_funcall(mrb, mrb_top_self(mrb), "load_story", 1, mrb_str_new_cstr(mrb, "scripts/story.rb"));
        mrb_print_error(mrb);
        mrb_print_backtrace(mrb);

        mrb_value story = mrb_funcall(mrb, mrb_top_self(mrb), "get_story", 0);

        play_story(mrb, story);
        

    }
    catch (const std::exception& e) {
        Debug::FatalError(e.what(), __FILE__, __LINE__);
    }

}

void Game::HandleEvents() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {

        /// Loop over all events in the SDL queue
        if (sdlEvent.type == SDL_EventType::SDL_QUIT) {
            isRunning = false;
        }
        if (sdlEvent.type == SDL_KEYDOWN) {
            switch (sdlEvent.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    isRunning = false;
                    return;
                case SDL_SCANCODE_SPACE:
                    player->play();
                    text_update_flag = true;
                    break;
                default:
                    break;
            }

        }

    }

}

void Game::Update(const float deltaTime) {
    if (player->currentDisplay.find("type") == player->currentDisplay.end()) {
        return;
    }
    if (player->currentDisplay["type"] == "description") {
        if (text_update_flag) {
            name_box->Update(" ", font, renderer);
            dialog_box->Update(player->currentDisplay["text"].c_str(), font, renderer);
            text_update_flag = false;
        }
    }
    if (player->currentDisplay["type"] == "dialogue") {
        std::cout << player->currentDisplay["character"] << player->currentDisplay["text"] << std::endl;
        if (text_update_flag) {
            name_box->Update(player->currentDisplay["character"].c_str(), font, renderer);
            dialog_box->Update(player->currentDisplay["text"].c_str(), font, renderer);
            text_update_flag = false;
        }
    }
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &dialog_box->rect);
    name_box->Draw(renderer);
    dialog_box->Draw(renderer);

    SDL_RenderPresent(renderer);
}

 