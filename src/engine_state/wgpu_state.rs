use std::sync::Arc;

use winit::{event_loop::ActiveEventLoop, keyboard::KeyCode, window::Window};

use crate::gpu_api::web_gpu::factories::*;

pub struct WgpuConfig {
    surface: wgpu::Surface<'static>,
    device: wgpu::Device,
    queue: wgpu::Queue,
    config: wgpu::SurfaceConfiguration,
    is_surface_configured: bool,
    window: Arc<Window>,
}

pub struct WgpuState {
    config: Option<WgpuConfig>,
}

impl WgpuState {
    pub const fn new() -> Self {
        return Self { config: None };
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

        *self = Self {
            config: Some(WgpuConfig {
                surface,
                device,
                queue,
                config,
                is_surface_configured: false,
                window,
            }),
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
