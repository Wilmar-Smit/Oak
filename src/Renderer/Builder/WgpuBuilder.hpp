#pragma once

#include <webgpu/webgpu_cpp.h>
#include <SDL3/SDL.h>
class WgpuBuilder {

  protected:
    wgpu::InstanceDescriptor instance_dsc;
    wgpu::RequestAdapterOptions adapter_options;
    wgpu::DeviceDescriptor device_dsc;
    wgpu::Instance createInstance();
    wgpu::Adapter createAdapter(wgpu::Instance inst);
    wgpu::Device createDevice(wgpu::Instance instance, wgpu::Adapter Adapter);
    wgpu::Queue createQueue(wgpu::Device);
    virtual wgpu::Surface createSurface(WGPUInstance instance, SDL_Window* window) = 0;

  public:
    auto createResourceManager();
    // Options where descriptors are remade separate from defaults
};
