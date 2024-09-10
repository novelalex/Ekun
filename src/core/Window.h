//
// Created by novel on 2024-09-08.
//

#ifndef EKUN_WINDOW_H
#define EKUN_WINDOW_H

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>
#include "Debug.h"

class Window {
private:
    int width, height;
    SDL_Window* window;
    SDL_GLContext context;
    // TODO
public:
    SDL_Renderer* renderer;

public:
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;

    Window();
    ~Window();
    bool OnCreate(const std::string& name_, int width_, int height_);
    void OnDestroy();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    SDL_Window* getWindow() const { return window; }

private: /// internal tools OpenGl versions.
    static void setAttributes(int major_, int minor_);
    static void getInstalledOpenGLInfo(int *major, int *minor);
};

#endif //EKUN_WINDOW_H
