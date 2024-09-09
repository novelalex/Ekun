//
// Created by novel on 2024-09-08.
//

#ifndef EKUN_GAMEMANAGER_H
#define EKUN_GAMEMANAGER_H

#include <string>
#include <memory>


class Timer;
class Window;
class Game;

class GameManager {
public:
    GameManager();
    ~GameManager();
    void Run();
    bool Initialize(const std::string& name_, int width_, int height_);
    void HandleEvents();
private:
    class Timer* timer;
    class Window* window;
    std::unique_ptr<Game> game;

    unsigned int fps;
    bool isRunning;
    bool fullScreen;
};


#endif //EKUN_GAMEMANAGER_H
