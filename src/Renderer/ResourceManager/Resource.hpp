#pragma once

#include <webgpu/webgpu_cpp.h>
namespace oak {
struct WGPU_Resources {
    wgpu::Instance instance;
    wgpu::Adapter adapter;
    wgpu::Device device;
    wgpu::Queue queue;
    wgpu::Surface surface;
};
} // namespace oak
