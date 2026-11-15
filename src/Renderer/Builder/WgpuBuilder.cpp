#include "WgpuBuilder.hpp"
#include <format>
#include <iostream>
#include <stdexcept>
#include <webgpu/webgpu_cpp.h>

wgpu::Instance WgpuBuilder::createInstance() {

    wgpu::Instance instance = wgpu::CreateInstance(&instance_dsc);
    return instance;
}

wgpu::Adapter WgpuBuilder::createAdapter(wgpu::Instance inst) {
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

auto WgpuBuilder::createPipeline() {}
