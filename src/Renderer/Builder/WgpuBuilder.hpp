#pragma once

#include <webgpu/webgpu_cpp.h>

class WgpuBuilder {

    wgpu::InstanceDescriptor instance_dsc;
    wgpu::RequestAdapterOptions adapter_options;
    wgpu::DeviceDescriptor device_dsc;

  private:
    wgpu::Instance createInstance();
    wgpu::Adapter createAdapter(wgpu::Instance inst);
    wgpu::Device createDevice(wgpu::Instance instance, wgpu::Adapter Adapter);
  public:
    auto createPipeline();
    // Options where descriptors are remade separate from defaults
};
