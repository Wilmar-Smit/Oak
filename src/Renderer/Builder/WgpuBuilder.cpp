#include "WgpuBuilder.hpp"
#include <format>
#include <iostream>
#include <stdexcept>
#include <webgpu/webgpu.h>
WGPUInstance WgpuBuilder::createInstance() {

    WGPUInstance instance = wgpuCreateInstance(&instance_dsc);
    return instance;
}

WGPUAdapter WgpuBuilder::createAdapter(WGPUInstance inst) {
    struct AdapterData {
        WGPUAdapter adapter = nullptr;
        bool requestEnded = false;
    };

    AdapterData adapterData;

    auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status, WGPUAdapter adapter,
                                    WGPUStringView message, void* pUserData1, void* pUserData2) {
        AdapterData& data = *reinterpret_cast<AdapterData*>(pUserData1);
        if (status == WGPURequestAdapterStatus_Success) {
            data.adapter = adapter;
            std::cout << "Adapter acquired successfully" << std::endl;
        } else {
            std::string_view msg(message.data ? message.data : "Unknown error",
                                 message.data ? message.length : 13);
            std::cerr << std::format("Adapter could not be created: {}\n", msg);
        }
        data.requestEnded = true;
    };

    WGPURequestAdapterCallbackInfo callbackInfo = {};
    callbackInfo.mode = WGPUCallbackMode_WaitAnyOnly;
    callbackInfo.callback = onAdapterRequestEnded;
    callbackInfo.userdata1 = &adapterData;

    WGPUFuture future = wgpuInstanceRequestAdapter(inst, &this->adapter_options, callbackInfo);

    WGPUFutureWaitInfo waitInfo = {};
    waitInfo.future = future;
    wgpuInstanceWaitAny(inst, 1, &waitInfo, UINT64_MAX);

    if (!adapterData.adapter) {
        throw std::runtime_error("Adapter could not be created.");
    }

    return adapterData.adapter;
}
WGPUDevice WgpuBuilder::createDevice(WGPUInstance instance, WGPUAdapter adapter) {
    struct DeviceData {
        WGPUDevice device = nullptr;
        bool requestEnded = false;
    };

    DeviceData deviceData;

    auto onDeviceRequestEnded = [](WGPURequestDeviceStatus status, WGPUDevice device,
                                   WGPUStringView message, void* pUserData, void* /*pUserData2*/) {
        DeviceData& deviceData = *reinterpret_cast<DeviceData*>(pUserData);
        if (status == WGPURequestDeviceStatus_Success) {
            deviceData.device = device;
            std::cout << "Device successfully acquired" << std::endl;
        } else {
            std::string_view msg(message.data ? message.data : "Unknown error",
                                 message.data ? message.length : 13);
            std::cerr << std::format("Failed to acquire Device: {}\n", msg);
        }
        deviceData.requestEnded = true;
    };

    WGPURequestDeviceCallbackInfo callbackInfo = {};
    callbackInfo.mode = WGPUCallbackMode_WaitAnyOnly;
    callbackInfo.callback = onDeviceRequestEnded;
    callbackInfo.userdata1 = &deviceData;

    WGPUFuture future = wgpuAdapterRequestDevice(adapter, &this->device_dsc, callbackInfo);

    WGPUFutureWaitInfo waitInfo = {};
    waitInfo.future = future;
    wgpuInstanceWaitAny(instance, 1, &waitInfo, UINT64_MAX);

    if (!deviceData.device) {
        throw std::runtime_error("Adapter could not be created.");
    }

    return deviceData.device;
}
