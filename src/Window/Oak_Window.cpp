#include "Oak_Window.hpp"
#include "Input/Input.hpp"
#include "Input/SDL_Input.hpp"
#include "Renderer/Builder/SDL3_Builder.hpp"
#include <memory>
#include <stdexcept>
using namespace oak;
Window::Window() {

    SDL_Init(SDL_INIT_VIDEO);

    this->window = SDL_CreateWindow("OAK", 640, 480, SDL_WINDOW_RESIZABLE);

    if (this->window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        throw std::runtime_error("Window could not be Created");
    } else {
        this->builder = new SDL3_Builder(window);
        this->wgpuResources = builder->createResourceManager();
    }
}

void Window::start() {

    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
            // game tree logic here
            // Followed by render logic
        }
    }

    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}

Window::~Window() {
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    if (builder) {
        delete builder;
        builder = nullptr;
    }
    if (this->wgpuResources) {
        delete wgpuResources;
        wgpuResources = nullptr;
    }
}

std::unique_ptr<Input> Window::PollEvents() {

    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        return std::make_unique<oak::SDL_Input>(event);
    } else
        return nullptr;
}
