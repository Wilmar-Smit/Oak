use std::sync::Arc;

use winit::{event_loop::ActiveEventLoop, keyboard::KeyCode, window::Window};

use crate::renderer::{
    self,
    wgpu_renderer::{self, WgpuRenderer},
};
use pollster::FutureExt;
use wgpu::{BackendOptions, InstanceFlags, MemoryBudgetThresholds, MemoryHints};
use winit::dpi::PhysicalSize;

pub struct WgpuConfig {
    pub surface: wgpu::Surface<'static>,
    pub device: wgpu::Device,
    pub queue: wgpu::Queue,
    pub config: wgpu::SurfaceConfiguration,
    pub is_surface_configured: bool,
    pub window: Arc<Window>,
}

pub struct WgpuState {
    config: Option<WgpuConfig>,
    renderer: Option<wgpu_renderer::WgpuRenderer>,
}

impl WgpuState {
    pub const fn new() -> Self {
        return Self {
            config: None,
            renderer: None,
        };
    }

    pub fn init(&mut self, window: Arc<Window>) {
        let size = window.inner_size();

        let instance = create_instance();

        let surface = instance
            .create_surface(window.clone())
            .expect("Surface Could not be Created");

        let adapter = create_adapter(&instance, &surface);

        let (device, queue) = create_device_queue(&adapter);

        let surface_caps = surface.get_capabilities(&adapter);

        let config = create_config(size, &surface_caps);

        let shader = device.create_shader_module(wgpu::ShaderModuleDescriptor {
            label: Some("Shader"),
            source: wgpu::ShaderSource::Wgsl(
                include_str!(concat!(
                    env!("CARGO_MANIFEST_DIR"),
                    "/assets/shaders/shader.wgsl"
                ))
                .into(),
            ),
        });

        let render_pipeline_layout =
            device.create_pipeline_layout(&wgpu::PipelineLayoutDescriptor {
                label: Some("Render Pipeline Layout"),
                bind_group_layouts: &[],
                immediate_size: 0,
            });

        let render_pipeline = device.create_render_pipeline(&wgpu::RenderPipelineDescriptor {
            label: Some("Render Pipeline"),
            layout: Some(&render_pipeline_layout),
            vertex: wgpu::VertexState {
                module: &shader,
                entry_point: Some("vs_main"),
                buffers: &[],
                compilation_options: wgpu::PipelineCompilationOptions::default(),
            },
            fragment: Some(wgpu::FragmentState {
                module: &shader,
                entry_point: Some("fs_main"),
                targets: &[Some(wgpu::ColorTargetState {
                    format: config.format,
                    blend: Some(wgpu::BlendState::REPLACE),
                    write_mask: wgpu::ColorWrites::ALL,
                })],
                compilation_options: wgpu::PipelineCompilationOptions::default(),
            }),
            primitive: wgpu::PrimitiveState {
                topology: wgpu::PrimitiveTopology::TriangleList,
                strip_index_format: None,
                front_face: wgpu::FrontFace::Ccw,
                cull_mode: Some(wgpu::Face::Back),
                polygon_mode: wgpu::PolygonMode::Fill,
                unclipped_depth: false,
                conservative: false,
            },
            depth_stencil: None,
            multisample: wgpu::MultisampleState {
                count: 1,
                mask: !0,
                alpha_to_coverage_enabled: false,
            },
            multiview_mask: None,
            cache: None,
        });

        let config = WgpuConfig {
            surface,
            device,
            queue,
            config,
            is_surface_configured: false,
            window,
        };

        let renderer = Some(WgpuRenderer::new(&config));

        *self = Self {
            config: Some(config),
            renderer,
        }
    }

    pub const fn update(&mut self) {
        // remove `todo!()`
    }

    pub fn resize(&mut self, width: u32, height: u32) {
        if let Some(config) = &mut self.config {
            if width > 0 && height > 0 {
                config.config.width = width;
                config.config.height = height;
                config.surface.configure(&config.device, &config.config);
                config.is_surface_configured = true;
            }
        } else {
            print!("Cannot Resize config is not initialized");
        }
    }

    #[allow(clippy::single_match)]
    pub fn handle_key(&self, event_loop: &ActiveEventLoop, code: KeyCode, is_pressed: bool) {
        match (code, is_pressed) {
            (KeyCode::Escape, true) => event_loop.exit(),
            _ => {}
        }
    }
}

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
