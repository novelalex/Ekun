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
    GameManager* manager;
    MRB::rb window_info;
    MRB::rb mouse_info;
public:
    Game();
    ~Game();
    bool OnCreate(GameManager *manager);
    void OnDestroy();
    void Init(SDL_Renderer* renderer);

    void reloadScript(SDL_Renderer* renderer);

    void HandleEvents(SDL_Renderer* renderer);
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer) ;

    void LoadSprites(SDL_Renderer *renderer, MRB::rb &load_hash);

    void RenderSpriteDestRect(SDL_Renderer * renderer, MRB::rb rb);

    void RenderFontWidth(SDL_Renderer * renderer, MRB::rb rb);

    void HandleOutputs(SDL_Renderer *renderer, MRB::rb &out_commands);

    void RenderSprite(SDL_Renderer *renderer, MRB::rb &command);
    void RenderSpriteFull(SDL_Renderer *renderer, MRB::rb &command);

    void LoadFonts(MRB::rb &load_hash);

    void RenderFont(SDL_Renderer *renderer, MRB::rb command);
    void CleanupTextures();
};

#endif //EKUN_GAME_H
