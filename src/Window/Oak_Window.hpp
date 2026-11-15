#pragma once

#include "Renderer/Builder/SDL3_Builder.hpp"
#include "Window/window.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class Oak_Window : Window {

  private:
    SDL_Window* window;
    SDL3_Builder* builder = nullptr;

  public:
    void start();
    Oak_Window();
    virtual ~Oak_Window();
};
