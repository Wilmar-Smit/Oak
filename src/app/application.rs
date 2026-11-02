use std::sync::Arc;

use winit::{
    application::ApplicationHandler,
    event::{self, WindowEvent},
    window::Window,
};

use crate::app::input::{self, InputHandler};

struct OakApp {
    window: Option<Arc<Window>>,
    input_handler: InputHandler,
}

impl OakApp {
    pub fn new() -> Self {
        Self {
            window: None,
            input_handler: InputHandler::new(),
        }
    }
}

impl ApplicationHandler for OakApp {
    fn resumed(&mut self, event_loop: &winit::event_loop::ActiveEventLoop) {
        if self.window.is_none() {
            let window_attributes = Window::default_attributes()
                .with_title("OAK")
                .with_inner_size(winit::dpi::LogicalSize::new(1280, 720));

            let window = Arc::new(
                event_loop
                    .create_window(window_attributes)
                    .expect("Window Creation Failed"),
            );
            self.window = Some(window);
        }
    }

    fn window_event(
        &mut self,
        event_loop: &winit::event_loop::ActiveEventLoop,
        _window_id: winit::window::WindowId,
        event: winit::event::WindowEvent,
    ) {
        match event {
            WindowEvent::CloseRequested => {
                println!("Close requested, exiting application.");
                event_loop.exit();
            }
            WindowEvent::Resized(physical_size) => {
                println!("Window resized to: {:?}", physical_size);
            }

            WindowEvent::KeyboardInput {
                event: key_event, ..
            } => {
                self.input_handler.handle_keyboard(&key_event);
            }
            WindowEvent::MouseInput { button, state, .. } => {
                self.input_handler.handle_mouse(state, button);
            }
            WindowEvent::CursorMoved { position, .. } => {
                self.input_handler.handle_cursor(position);
            }

            _ => {}
        }
    }
}
