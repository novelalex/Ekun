//
// Created by novel on 2024-09-08.
//

#include "Game.h"

Game::Game(): mrb{nullptr}, args{}, game_instance{} {

}

Game::~Game() {
    OnDestroy();
}

bool Game::OnCreate() {
    mrb = new MRuby();
    mrb->LoadFile("scripts/main.rb");
    args = mrb->NewHash();
    rb output = mrb->NewArray();

    return true;
}

void Game::OnDestroy() {
    delete mrb;
}

void Game::Init() {



}

void Game::HandleEvents(const SDL_Event &sdlEvent) {

}

void Game::Update(const float deltaTime) {

}

void Game::Render() const {

}

