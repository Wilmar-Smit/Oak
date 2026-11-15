#include "SDL3_Builder.hpp"
#include "sdl3webgpu.h"
namespace oak {

wgpu::Surface SDL3_Builder::createSurface(WGPUInstance instance) {

    wgpu::Surface surface = SDL_GetWGPUSurface(instance, this->window);
    this->adapter_options.compatibleSurface = surface;

    return surface;
}
SDL3_Builder::SDL3_Builder(SDL_Window* window) : window(window) {}
} // namespace oak
