//
// Created by novel on 2024-09-08.
//

#ifndef EKUN_GAME_H
#define EKUN_GAME_H

#include <SDL.h>
#include "../scripting/MRuby.h"
class Game {
private:
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
    void Init();
    void HandleEvents(const SDL_Event &sdlEvent);
    void Update(float deltaTime);
    void Render() const;
};

#endif //EKUN_GAME_H
