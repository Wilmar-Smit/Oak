mod app;
mod gpu_api;
mod state;
use app::application::OakApp;
use winit::event_loop::{ControlFlow, EventLoop};

fn main() -> Result<(), winit::error::EventLoopError> {
    env_logger::init();

    let event_loop = EventLoop::new().expect("Failed to build event loop");
    event_loop.set_control_flow(ControlFlow::Poll);
    let mut oak_app = OakApp::new();
    event_loop.run_app(&mut oak_app)
}
