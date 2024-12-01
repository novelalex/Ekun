//
// Created by novel on 2024-09-08.
//

#ifndef EKUN_GAME_H
#define EKUN_GAME_H

#include <memory>
#include <SDL.h>
#include <unordered_map>

#include "GameManager.h"
#include "../graphics/Sprite.h"
#include "../scripting/MRuby.h"
#include "../scripting/Script.h"
#include "SDL_ttf.h"
#include "../graphics/Font.h"


class Game {
private:
    mrb_state* mrb;
public:
    Game();
    ~Game();

    bool isRunning;

    bool OnCreate();
    void OnDestroy();
    void Init();
    void HandleEvents();
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer) ;
};

#endif //EKUN_GAME_H
