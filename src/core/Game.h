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
#include "../scripting/Script.h"
#include "SDL_ttf.h"
#include "../graphics/Font.h"

struct Assets {
    std::unordered_map<std::string, Sprite*> sprites;
    std::unordered_map<std::string, Font*> fonts;
};

class Game {
private:
    Assets assets;
    mrb_state* mrb{};
    Script script;
    std::vector<SDL_Texture*> textures_to_destroy;
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

    void LoadSprites(SDL_Renderer *renderer, MRB::rb &load_hash);

    void HandleOutputs(SDL_Renderer *renderer, MRB::rb &out_commands);

    void RenderSpriteDest(SDL_Renderer *renderer, MRB::rb &command);

    void LoadFonts(MRB::rb &load_hash);

    void RenderFont(SDL_Renderer *renderer, MRB::rb command);
    void CleanupTextures();
};

#endif //EKUN_GAME_H
