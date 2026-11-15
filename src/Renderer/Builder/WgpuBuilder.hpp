#pragma once

#include <webgpu/webgpu.h>
class WgpuBuilder {

    WGPUInstanceDescriptor instance_dsc;
    WGPURequestAdapterOptions  adapter_options;

  private:
    WGPUInstance createInstance();

    // Cleans the instance
    WGPUAdapter createAdapter(WGPUInstance inst);
    WGPUDevice createDevice(WGPUInstance Adapter);

  public:
    auto createPipeline();
    // Options where descriptors are remade separate from defaults
};
