#pragma once

#include "Renderer/Builder/SDL3_Builder.hpp"
#include "Renderer/ResourceManager/ResourceManager.hpp"
#include "Window/Iwindow.hpp"
#include <SDL3/SDL.h>

namespace oak {

class Window : oak::Iwindow {

  private:
    ResourceManager* wgpuResources = nullptr;
    SDL_Window* window = nullptr;
    SDL3_Builder* builder = nullptr;

  public:
    void start() override;
    std::unique_ptr<Input> PollEvents() override;
    Window();
    ~Window() override;
};
} // namespace oak
