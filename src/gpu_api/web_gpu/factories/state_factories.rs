use pollster::FutureExt;
use wgpu::{BackendOptions, InstanceFlags, MemoryBudgetThresholds, MemoryHints};
use winit::dpi::PhysicalSize;

pub fn create_instance() -> wgpu::Instance {
    return wgpu::Instance::new(wgpu::InstanceDescriptor {
        backends: wgpu::Backends::PRIMARY,
        flags: InstanceFlags::default(),
        memory_budget_thresholds: MemoryBudgetThresholds::default(),
        backend_options: BackendOptions::default(),
        display: None,
    });
}

pub fn create_adapter(inst: &wgpu::Instance, surface: &wgpu::Surface<'_>) -> wgpu::Adapter {
    return (inst.request_adapter(&wgpu::RequestAdapterOptions {
        power_preference: wgpu::PowerPreference::default(),
        compatible_surface: Some(surface),
        force_fallback_adapter: false,
        apply_limit_buckets: true,
    }))
    .block_on()
    .expect("Could not Create Adapter");
}

pub fn create_device_queue(adapter: &wgpu::Adapter) -> (wgpu::Device, wgpu::Queue) {
    let (device, queue) = (adapter.request_device(&wgpu::DeviceDescriptor {
        label: None,
        required_features: wgpu::Features::empty(),
        required_limits: wgpu::Limits::default(),
        memory_hints: MemoryHints::default(),
        trace: wgpu::Trace::Off,
        experimental_features: wgpu::ExperimentalFeatures::disabled(),
    }))
    .block_on()
    .expect("Could not request device or queue");

    return (device, queue);
}

pub fn create_config(
    size: PhysicalSize<u32>,
    surface_caps: &wgpu::SurfaceCapabilities,
) -> wgpu::SurfaceConfiguration {
    let surface_format = surface_caps
        .formats
        .iter()
        .find(|f| f.is_srgb())
        .copied()
        .unwrap_or(surface_caps.formats[0]);

    return wgpu::SurfaceConfiguration {
        usage: wgpu::TextureUsages::RENDER_ATTACHMENT,
        format: surface_format,
        width: size.width,
        height: size.height,
        present_mode: surface_caps.present_modes[0],
        alpha_mode: surface_caps.alpha_modes[0],
        view_formats: vec![],
        desired_maximum_frame_latency: 2,
        color_space: wgpu::SurfaceColorSpace::Auto,
    };
}
