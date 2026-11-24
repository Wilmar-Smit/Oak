#pragma once

#include "Window/Iwindow.hpp"
#include <SDL3/SDL.h>
#include <memory>

namespace oak {

class Window : oak::Iwindow {

  private:
    SDL_Window* window = nullptr;

  public:
    std::expected<bool, std::string> init_window() override;
    std::expected<std::unique_ptr<ResourceManager>, std::string> init_resources() override;
    void start() override;
    std::unique_ptr<Input> PollEvents() override;
    Window();
    ~Window() override;
};
} // namespace oak
