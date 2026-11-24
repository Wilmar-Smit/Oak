#include "App.hpp"
#include "Input/Input.hpp"
#include "Window/Iwindow.hpp"
#include "Window/Oak_Window.hpp"
#include <expected>
#include <memory>
#include <string>
#include <utility>

namespace oak {

App::App() {}

expected<bool, string> App::init(Iwindow* window) {
    this->window = std::unique_ptr<Iwindow>(window);

    auto window_init = window->init_window();
    if (!window_init) {
        return std::unexpected(std::move(window_init.error()));
    }

    auto resource_init = window->init_resources();
    if (!resource_init) {
        return std::unexpected<std::string>(resource_init.error());
    }
    gpu_resources = std::move(*resource_init);
    return true;
}

expected<bool, string> App::start_loop() {
    window->start();
    std::unique_ptr<Input> event;
    bool running = true;

    while (running) {

        if (event) {

            switch (event->type) {
            case oak::Input_Type::CLOSE: {
                running = false;
                break;
            }
            default: {
            }
            }
        }
        // game engine
        // Renderer
    }
}
} // namespace oak
