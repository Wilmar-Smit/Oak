mod app;
mod engine_state;
mod gpu_api;
use app::application::OakApp;
use winit::event_loop::{ControlFlow, EventLoop};

use crate::engine_state::{api_state, wgpu_state::wgpu_state};

fn main() -> Result<(), winit::error::EventLoopError> {
    env_logger::init();

    let event_loop = EventLoop::new().expect("Failed to build event loop");
    event_loop.set_control_flow(ControlFlow::Poll);

    let mut oak_app = OakApp::new(api_state::ApiState::WgpuState {
        state: wgpu_state::new(),
    });

    event_loop.run_app(&mut oak_app)
}
