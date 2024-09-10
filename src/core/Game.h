//
// Created by novel on 2024-09-08.
//

#ifndef EKUN_GAME_H
#define EKUN_GAME_H

#include <memory>
#include <SDL.h>
#include <unordered_map>

#include "../graphics/Sprite.h"
#include "../scripting/MRuby.h"

struct Assets {
    std::unordered_map<std::string, Sprite*> sprites;
};

class Game {
private:
    Assets assets;
    mrb_state* mrb;
    MRB::rb args; // Hash that gets passed in to every function, I think that's how DragonRuby does it
    MRB::rb game_instance; // This is gonna be the game script from ruby
    MRB::rb load;
    MRB::rb output;
    MRB::rb input;
    MRB::rb config;
    MRB::rb state;
public:
    Game();
    ~Game();
    bool OnCreate();
    void OnDestroy();
    void Init(SDL_Renderer* renderer);

    void reloadScript(SDL_Renderer* renderer);

    void HandleEvents(SDL_Event &sdlEvent, SDL_Renderer* renderer);
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer) ;
};

#endif //EKUN_GAME_H
