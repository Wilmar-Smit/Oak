#pragma once

#include "Renderer/Builder/WgpuBuilder.hpp"

class SDL3_Builder : public oak::WgpuBuilder {
  protected:
    wgpu::Surface createSurface(WGPUInstance instance) override;
    SDL_Window* window = nullptr; // not owned

  public:
    explicit SDL3_Builder(SDL_Window* window);
    ~SDL3_Builder() override {};
};
