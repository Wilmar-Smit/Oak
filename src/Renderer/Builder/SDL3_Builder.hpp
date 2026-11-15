#pragma once

#include "Renderer/Builder/WgpuBuilder.hpp"
#include <webgpu/webgpu_cpp.h>
class SDL3_Builder : public WgpuBuilder {

    virtual wgpu::Surface createSurface();
};
