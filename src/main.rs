mod oak_app;
use crate::oak_app::app::Oak;
use winit::event_loop::{ControlFlow, EventLoop};

fn main() {
    let event_loop = EventLoop::new().expect("Event loop could not be created");
    event_loop.set_control_flow(ControlFlow::Poll);
    let mut app = Oak::new();
    event_loop.run_app(&mut app).expect("Run app failed");
}
