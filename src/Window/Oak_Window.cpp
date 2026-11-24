#include "Oak_Window.hpp"
#include "Input/Input.hpp"
#include "Input/SDL_Input.hpp"
#include "Renderer/Builder/SDL3_Builder.hpp"
#include "Renderer/Builder/WgpuBuilder.hpp"

#include "Renderer/ResourceManager/ResourceManager.hpp"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"
#include <memory>
#include <stdexcept>
#include <string>
using namespace oak;
Window::Window() {}

std::expected<bool, std::string> Window::init_window() {
    SDL_Init(SDL_INIT_VIDEO);

    this->window = SDL_CreateWindow("OAK", 640, 480, SDL_WINDOW_RESIZABLE);

    if (this->window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return "Failed to initialise SDL window";
    } else {
        return true;
    }
}
std::expected<std::unique_ptr<ResourceManager>, std::string> Window::init_resources() {
    std::unique_ptr<WgpuBuilder> builder = std::make_unique<SDL3_Builder>(this->window);
    ResourceManager* resources = nullptr;
    try {
        resources = builder->createResourceManager();
    } catch (std::runtime_error err) {
        return std::unexpected(err.what());
    } catch (...) {
        return std::unexpected("Unhandled Exception in SDL3 Resource Maker");
    }

    return std::unique_ptr<ResourceManager>(resources);
}

void Window::start() { SDL_ShowWindow(this->window); }

Window::~Window() {
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

std::unique_ptr<Input> Window::PollEvents() {

    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        return std::make_unique<oak::SDL_Input>(event);
    } else
        return nullptr;
}
