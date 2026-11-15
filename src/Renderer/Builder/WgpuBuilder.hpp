#pragma once

#include <webgpu/webgpu.h>
class WgpuBuilder {

    WGPUInstanceDescriptor instance_dsc;

  private:
    WGPUInstance createInstance();

    // Cleans the instance
    WGPUAdapter createAdapter(WGPUInstance inst);
    WGPUDevice createDevice(WGPUInstance inst);

  public:
    // Options where descriptors are remade separate from defaults
};
