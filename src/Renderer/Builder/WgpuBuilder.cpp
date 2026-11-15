#include "WgpuBuilder.hpp"
#include "Renderer/ResourceManager/Resource.hpp"
#include "Renderer/ResourceManager/ResourceManager.hpp"
#include <format>
#include <iostream>
#include <stdexcept>
#include <webgpu/webgpu_cpp.h>
using namespace oak;
wgpu::Instance WgpuBuilder::createInstance() {
    static constexpr wgpu::InstanceFeatureName kRequiredFeatures[] = {
        wgpu::InstanceFeatureName::TimedWaitAny,
    };

    wgpu::InstanceDescriptor& desc = this->instance_dsc;

    if (!desc.requiredFeatures) {
        desc.requiredFeatureCount = 1;
        desc.requiredFeatures = kRequiredFeatures;
    }

    wgpu::InstanceLimits limits = {};
    bool setDefaultLimits = false;
    if (!desc.requiredLimits) {
        limits.timedWaitAnyMaxCount = 1;
        desc.requiredLimits = &limits;
        setDefaultLimits = true;
    }

    wgpu::Instance instance = wgpu::CreateInstance(&desc);

    if (setDefaultLimits) {
        desc.requiredLimits = nullptr;
    }

    if (!instance) {
        throw std::runtime_error("Failed to create WebGPU Instance.");
    }
    return instance;
}

wgpu::Adapter WgpuBuilder::createAdapter(wgpu::Instance inst) {

    if (adapter_options.compatibleSurface == nullptr) {
        std::cerr << "Surface not set before adapter" << std::endl;
    }

    struct AdapterData {
        wgpu::Adapter adapter = nullptr;
        bool requestEnded = false;
    };

    AdapterData adapterData;

    auto onAdapterRequestEnded = [&adapterData](wgpu::RequestAdapterStatus status,
                                                wgpu::Adapter adapter, wgpu::StringView message) {
        if (status == wgpu::RequestAdapterStatus::Success) {
            adapterData.adapter = adapter;
            std::cout << "Adapter acquired successfully" << std::endl;
        } else {
            std::string_view msg(message.data ? message.data : "Unknown error",
                                 message.data ? message.length : 13);
            std::cerr << std::format("Adapter could not be created: {}\n", msg);
        }
        adapterData.requestEnded = true;
    };

    wgpu::Future future = inst.RequestAdapter(
        &this->adapter_options, wgpu::CallbackMode::WaitAnyOnly, onAdapterRequestEnded);

    wgpu::FutureWaitInfo waitInfo = {};
    waitInfo.future = future;
    inst.WaitAny(1, &waitInfo, UINT64_MAX);

    if (!adapterData.adapter) {
        throw std::runtime_error("Adapter could not be created.");
    }

    return adapterData.adapter;
}

wgpu::Device WgpuBuilder::createDevice(wgpu::Instance instance, wgpu::Adapter adapter) {
    struct DeviceData {
        wgpu::Device device = nullptr;
        bool requestEnded = false;
    };

    DeviceData deviceData;

    auto onDeviceRequestEnded = [&deviceData](wgpu::RequestDeviceStatus status, wgpu::Device device,
                                              wgpu::StringView message) {
        if (status == wgpu::RequestDeviceStatus::Success) {
            deviceData.device = device;
            std::cout << "Device successfully acquired" << std::endl;
        } else {
            std::string_view msg(message.data ? message.data : "Unknown error",
                                 message.data ? message.length : 13);
            std::cerr << std::format("Failed to acquire Device: {}\n", msg);
        }
        deviceData.requestEnded = true;
    };

    wgpu::Future future = adapter.RequestDevice(&this->device_dsc, wgpu::CallbackMode::WaitAnyOnly,
                                                onDeviceRequestEnded);

    wgpu::FutureWaitInfo waitInfo = {};
    waitInfo.future = future;
    instance.WaitAny(1, &waitInfo, UINT64_MAX);

    if (!deviceData.device) {
        throw std::runtime_error("Device could not be created.");
    }

    return deviceData.device;
}

wgpu::Queue WgpuBuilder::createQueue(wgpu::Device device) { return device.GetQueue(); }

wgpu::Surface WgpuBuilder::createSurface(wgpu::Instance /* Headless surface */) {
    return wgpu::Surface(nullptr);
}

ResourceManager* WgpuBuilder::createResourceManager() {
    wgpu::Instance instance = createInstance();
    wgpu::Surface surface = createSurface(instance);
    wgpu::Adapter adapter = createAdapter(instance);
    wgpu::Device device = createDevice(instance, adapter);
    wgpu::Queue queue = createQueue(device);

    WGPU_Resources* resources = new WGPU_Resources{
        .instance = std::move(instance),
        .adapter = std::move(adapter),
        .device = std::move(device),
        .queue = std::move(queue),
        .surface = std::move(surface),
    };
    return new ResourceManager(resources);
}
