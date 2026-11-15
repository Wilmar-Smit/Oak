#include "Window/Oak_Window.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <webgpu/webgpu.h>

int main() {

    oak::Window* window = nullptr;
    try {
        window = new oak::Window();
        window->start();
    } catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
    }

    if (window) {
        delete window;
    }

    return 0;
}
