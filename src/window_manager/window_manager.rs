use std::{fmt, sync::Arc};

use winit::{
    application::ApplicationHandler,
    event::WindowEvent,
    event_loop::{self, ActiveEventLoop, EventLoop},
    keyboard::NamedKey::New,
    window::{Window, WindowAttributes, WindowId},
};

pub struct WindowManager {
    window: Option<Arc<Window>>,
}

impl WindowManager {
    fn new() -> Self {
        Self { window: None }
    }

    pub fn run() -> Result<(), winit::error::EventLoopError> {
        let event_loop = EventLoop::new().expect("Event Loop could not be Created");
        let mut manager = Self::new();
        return event_loop.run_app(&mut manager);
    }
}

impl ApplicationHandler for WindowManager {
    fn resumed(&mut self, event_loop: &ActiveEventLoop) {
        if self.window.is_none() {
            let attributes = WindowAttributes::default().with_title("Oak");
            let window = event_loop
                .create_window(attributes)
                .expect("Failed to Create Window");
            self.window = Some(Arc::new(window));
        }
    }

    fn window_event(
        &mut self,
        event_loop: &ActiveEventLoop,
        window_id: WindowId,
        event: WindowEvent,
    ) {
        match event {
            WindowEvent::CloseRequested => event_loop.exit(),
            WindowEvent::Resized(size) => {
                print!("Size changed  X {}, Y{}  ", size.width, size.height)
            }
            WindowEvent::RedrawRequested => {}
            _ => print!("Event was captured"),
        }
    }
}
