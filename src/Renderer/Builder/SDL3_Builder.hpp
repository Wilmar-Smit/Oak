#pragma once

#include "Renderer/Builder/WgpuBuilder.hpp"

class SDL3_Builder : public WgpuBuilder {
  protected:
    wgpu::Surface createSurface(WGPUInstance instance) override;
    SDL_Window* window = nullptr; // not owned

  public:
    explicit SDL3_Builder(SDL_Window* window);
    virtual ~SDL3_Builder() {};
};
