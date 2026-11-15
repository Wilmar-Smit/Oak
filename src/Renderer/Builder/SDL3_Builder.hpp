#pragma once

#include "Renderer/Builder/WgpuBuilder.hpp"

class SDL3_Builder : public WgpuBuilder {

    virtual wgpu::Surface createSurface(WGPUInstance instance, SDL_Window* window) override;
};
