#include "SDL3_Builder.hpp"
#include "sdl3webgpu.h"

wgpu::Surface SDL3_Builder::createSurface(WGPUInstance instance, SDL_Window* window) {

    wgpu::Surface surface = SDL_GetWGPUSurface(instance, window);
    this->adapter_options.compatibleSurface = surface;

    return surface;
}
