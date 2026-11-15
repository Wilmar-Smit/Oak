#include "WgpuBuilder.hpp"
#include <webgpu/webgpu.h>

WGPUInstance WgpuBuilder::createInstance() {

    WGPUInstance instance = wgpuCreateInstance(&instance_dsc);
    return instance;
}
