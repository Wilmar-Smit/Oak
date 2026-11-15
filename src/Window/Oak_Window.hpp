#pragma once

#include "Renderer/Builder/SDL3_Builder.hpp"
#include "Window/window.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

namespace oak {

class Window : oak::abstract_Window {

  private:
    SDL_Window* window;
    SDL3_Builder* builder = nullptr;

  public:
    void start() override;
    Window();
    ~Window() override;
};
} // namespace oak
