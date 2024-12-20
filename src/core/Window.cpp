//
// Created by novel on 2024-09-08.
//

#include "Window.h"
#include "SDL_ttf.h"

#include <SDL_image.h>

Window::Window(): window{nullptr}, context{nullptr},  width{0}, height{0} {}

Window::~Window() {
    OnDestroy();
}

bool Window::OnCreate(const std::string& name_, int width_, int height_){
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        Debug::FatalError("Failed to initialize SDL", __FILE__, __LINE__);
        return false;
    }

    this->width = width_;
    this->height = height_;
    window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                              width, height,SDL_WINDOW_OPENGL);

    if (window == nullptr) {
        Debug::FatalError("Failed to create a window", __FILE__, __LINE__);
        return false;
    }

    // TODO
    //Initialize PNG loading
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return false;
    }

    if (TTF_Init() < 0) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }
    // context = SDL_GL_CreateContext(window);
    // int major, minor;
    // getInstalledOpenGLInfo(&major,&minor);
    // setAttributes(major,minor);
    // /// Fire up the GL Extension Wrangler (GLEW)
    // GLenum err = glewInit();
    // if (err != GLEW_OK) {
    //     Debug::FatalError("Glew initialization failed", __FILE__, __LINE__);
    //     return false;
    // }
    // glViewport(0, 0, width, height);

    return true;
}

void Window::OnDestroy() {
    // TODO
    // SDL_GL_DeleteContext(context);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    window = nullptr;
}


void Window::getInstalledOpenGLInfo(int *major, int *minor) {
    /// You can to get some info regarding versions and manufacturer
    const GLubyte *version = glGetString(GL_VERSION);
    /// You can also get the version as ints
    const GLubyte *vendor = glGetString(GL_VENDOR);
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);


    glGetIntegerv(GL_MAJOR_VERSION, major);
    glGetIntegerv(GL_MINOR_VERSION, minor);
    Debug::Info("OpenGL version: " + std::string((char*)glGetString(GL_VERSION)), __FILE__, __LINE__);
    Debug::Info("Graphics card vendor " + std::string((char*)vendor), __FILE__, __LINE__);
    Debug::Info("Graphics card name " + std::string((char*)renderer), __FILE__, __LINE__);
    Debug::Info("GLSL Version " + std::string((char*)glslVersion), __FILE__, __LINE__);
}

void Window::setAttributes(int major_, int minor_) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major_);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor_);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

    SDL_GL_SetSwapInterval(1);
    glewExperimental = GL_TRUE;
}

