//
// Created by novel on 2024-09-08.
//

#include "GameManager.h"
#include "Debug.h"
#include "Window.h"
#include "Timer.h"
#include "Game.h"

GameManager::GameManager():window{nullptr}, timer{nullptr}, fps{60}, isRunning{false}, fullScreen{false} {
    Debug::Info("Starting the GameManager", __FILE__, __LINE__);
}

GameManager::~GameManager() {
    Debug::Info("Deleting the SceneManager", __FILE__, __LINE__);

    if (timer) {
        delete timer;
        timer = nullptr;
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
    game = std::make_unique<Game>();
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
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) { /// Loop over all events in the SDL queue
        if (sdlEvent.type == SDL_EventType::SDL_QUIT) {
            isRunning = false;
            return;
        }
        else if (sdlEvent.type == SDL_KEYDOWN) {
            switch (sdlEvent.key.keysym.scancode) {
                //[[fallthrough]]; /// C17 Prevents switch/case fallthrough warnings
                case SDL_SCANCODE_ESCAPE:
                    isRunning = false;
                    return;

                default:
                    break;
            }
        }
        if (game == nullptr) { /// Just to be careful
            Debug::FatalError("No Game:", __FILE__, __LINE__);
            isRunning = false;
            return;
        }
        game->HandleEvents(sdlEvent);
    }
}
