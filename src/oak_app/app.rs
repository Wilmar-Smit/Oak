use winit::application::ApplicationHandler;
use winit::event::WindowEvent;
use winit::event_loop::{ActiveEventLoop, ControlFlow, EventLoop};
use winit::window::{Window, WindowAttributes, WindowId};

#[derive(Default)]
pub struct Oak {
    window: Option<Window>,
}
impl Oak {
    pub const fn new() -> Self {
        Self { window: None }
    }
}

impl ApplicationHandler for Oak {
    fn resumed(&mut self, event_loop: &ActiveEventLoop) {
        let attributes = Window::default_attributes().with_title("Oak");

        let window = event_loop
            .create_window(attributes)
            .expect("Create Window Failed");

        self.window = Some(window);
    }

    fn window_event(&mut self, event_loop: &ActiveEventLoop, id: WindowId, event: WindowEvent) {
        if let Some(window) = &self.window {
            match event {
                WindowEvent::CloseRequested => {
                    println!("The close button was pressed; stopping");
                    event_loop.exit();
                }
                WindowEvent::RedrawRequested => {
                    window.request_redraw();
                }
                _ => (),
            }
        } else {
            panic!("No Window Created")
        }
    }
}
