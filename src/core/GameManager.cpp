//
// Created by novel on 2024-09-08.
//

#include "GameManager.h"
#include "Debug.h"
#include "Window.h"
#include "Timer.h"
#include "Game.h"

GameManager::GameManager():window{nullptr}, timer{nullptr}, fps{60}, isRunning{false}, fullScreen{false}, game{nullptr} {
    Debug::Info("Starting the GameManager", __FILE__, __LINE__);
}

GameManager::~GameManager() {
    Debug::Info("Deleting the SceneManager", __FILE__, __LINE__);

    if (timer) {
        delete timer;
        timer = nullptr;
    }

    if (game) {
        delete game;
        game = nullptr;
    }

    if (window) {
        delete window;
        window = nullptr;
    }


}

bool GameManager::Initialize(const std::string& name_, int width_, int height_) {
    window = new Window();
    if (!window->OnCreate(name_, width_, height_)) {
        Debug::FatalError("Failed to initialize Window object", __FILE__, __LINE__);
        return false;
    }

    timer = new Timer();
    if (timer == nullptr) {
        Debug::FatalError("Failed to initialize Timer object", __FILE__, __LINE__);
        return false;
    }

    // INIT GAME
    game = new Game();
    if(!game->OnCreate()){
        Debug::FatalError("Failed to initialize Game", __FILE__, __LINE__);
        return false;
    }
    return true;
}

void GameManager::Run() {
    timer->Start();
    isRunning = true;
    game->Init(window->renderer);
    while (isRunning) {
        HandleEvents();
        timer->UpdateFrameTicks();
        game->Update(timer->GetDeltaTime());
        game->Render(window->renderer);

       // SDL_GL_SwapWindow(window->getWindow());
        SDL_Delay(timer->GetSleepTime(fps));

    }
}


void GameManager::HandleEvents() {
        game->HandleEvents(window->renderer, this);
    }
