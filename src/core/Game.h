//
// Created by novel on 2024-09-08.
//

#ifndef EKUN_GAME_H
#define EKUN_GAME_H

#include <memory>
#include <SDL.h>
#include <unordered_map>
#include "StoryPlayer.h"
#include "GameManager.h"
#include "../graphics/Sprite.h"
#include "../scripting/MRuby.h"
#include "../scripting/Script.h"
#include "SDL_ttf.h"
#include "../graphics/Font.h"
#include "../graphics/TextBox.h"
#include "../graphics/Button.h"

class Game {
private:
    mrb_state* mrb;
    StoryPlayer* player;
    SDL_Renderer* renderer;
    Font* font;
    TextBox* dialog_box;
    TextBox* name_box;
    Sprite* dialog_bg;
    bool text_update_flag;
    std::vector<Button*> choice_buttons;
    std::unordered_map<std::string, Sprite*> character_sprites;
    void CreateChoiceButtons();
    void ClearChoiceButtons();

public:
    Game(SDL_Renderer* renderer);
    ~Game();

    bool isRunning;

    bool OnCreate();
    void OnDestroy();
    void Init();
    void HandleEvents();
    void Update(float deltaTime);
    void Render();
    void play_story(mrb_state* mrb, mrb_value story);
};

#endif //EKUN_GAME_H
