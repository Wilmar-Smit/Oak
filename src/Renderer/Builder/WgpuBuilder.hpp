#pragma once

#include "Renderer/ResourceManager/ResourceManager.hpp"
#include <SDL3/SDL.h>
#include <webgpu/webgpu_cpp.h>
namespace oak {

class WgpuBuilder {

  protected:
    wgpu::InstanceDescriptor instance_dsc;
    wgpu::RequestAdapterOptions adapter_options;
    wgpu::DeviceDescriptor device_dsc;

  public:
    ResourceManager* createResourceManager();
    wgpu::Instance createInstance();
    wgpu::Adapter createAdapter(wgpu::Instance inst);
    wgpu::Device createDevice(wgpu::Instance instance, wgpu::Adapter Adapter);
    wgpu::Queue createQueue(wgpu::Device);
    virtual wgpu::Surface createSurface(wgpu::Instance);
    virtual ~WgpuBuilder() {}
    // Options where descriptors are remade separate from defaults
};
} // namespace oak
