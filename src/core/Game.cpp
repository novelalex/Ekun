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

void Game::CreateChoiceButtons() {
    ClearChoiceButtons();

    int w = 400;
    int h = 50;
    int space = 20;
    int initial_y = 300;

    for (size_t i = 0; i < player->currentChoices.size(); i++) {
        int y = initial_y + (h + space) * i;
        Button* button = new Button(
            (1280 - w) / 2,
            y,
            w,
            h,
            player->currentChoices[i]
        );
        choice_buttons.push_back(button);
    }
}

void Game::ClearChoiceButtons() {
    for (Button* button : choice_buttons) {
        delete button;
    }
    choice_buttons.clear();
}


Game::Game(SDL_Renderer* r) : isRunning{ true }, renderer{r} {
}

Game::~Game() {
    OnDestroy();
}


bool Game::OnCreate() {
    font = new Font("fonts/Montserrat-Regular.ttf", 24);
    dialog_box = new TextBox(55, 565, 1200, 300);
    name_box = new TextBox(70, 510, 1000, 300);
    text_update_flag = true;
    dialog_bg = new Sprite("sprites/HUD.png", renderer);



    return true;
}


void Game::OnDestroy() {
    delete dialog_box;
    delete name_box;
    delete player;
    delete font;
    delete dialog_bg;
    ClearChoiceButtons();
    mrb_close(mrb);
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


        mrb_value characters = mrb_funcall(mrb, story, "characters", 0);
        mrb_value char_arr = mrb_funcall(mrb, characters, "keys", 0);
        mrb_print_error(mrb);
        mrb_print_backtrace(mrb);
        for (int i = 0; i < RARRAY_LEN(char_arr); i++) {
            mrb_value character = mrb_hash_get(mrb, characters, mrb_ary_entry(char_arr, i));
            mrb_funcall(mrb, mrb_top_self(mrb), "puts", 1, character);

            mrb_value mrb_path = mrb_hash_get(mrb, character, mrb_symbol_value(mrb_intern_cstr(mrb, "path")));
            std::string path = mrb_str_to_cstr(mrb, mrb_path);
            character_sprites[path] = new Sprite(path, renderer);
        }

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

        if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX;
            int mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            if (player->currentDisplay["type"] == "choice") {
                for (size_t i = 0; i < choice_buttons.size(); i++) {
                    if (choice_buttons[i]->IsMouseOver(mouseX, mouseY)) {
                        // Handle choice selection
                        ClearChoiceButtons();
                        player->post_choice(i);
                        player->play();
                        text_update_flag = true;
                        break;
                    }
                }
            }
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
        //std::cout << player->currentDisplay["character"] << player->currentDisplay["text"] << std::endl;
        if (text_update_flag) {
            name_box->Update(player->currentDisplay["character"].c_str(), font, renderer);
            dialog_box->Update(player->currentDisplay["text"].c_str(), font, renderer);
            text_update_flag = false;
        }
    }

    if (player->currentDisplay["type"] == "choice") {
        if (text_update_flag) {
            CreateChoiceButtons();
            text_update_flag = false;
        }
    }
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderDrawRect(renderer, &dialog_box->rect);

    if (player->currentDisplay["type"] == "dialogue") {
        character_sprites[player->currentDisplay["path"].c_str()]->Draw(renderer, -850, -150);
    }

    dialog_bg->Draw(renderer, 0, 0);
    name_box->Draw(renderer);
    dialog_box->Draw(renderer);
    if (player->currentDisplay["type"] == "choice") {
        for (Button* button : choice_buttons) {
            button->Draw(renderer, font);
        }
    }
    SDL_RenderPresent(renderer);
}

 