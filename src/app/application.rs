use std::sync::Arc;

use winit::{application::ApplicationHandler, event::WindowEvent, window::Window};

use crate::{app::input::InputHandler, engine_state::api_state::ApiState};

pub struct OakApp {
    window: Option<Arc<Window>>,
    input_handler: InputHandler,
    api_state: ApiState,
}

impl OakApp {
    pub const fn new(api_state: ApiState) -> Self {
        Self {
            window: None,
            input_handler: InputHandler::new(),
            api_state,
        }
    }
    pub fn init_state(&mut self) {
        match &mut self.api_state {
            ApiState::WgpuState { state } => {
                if let Some(window) = self.window.clone() {
                    state.init(window);
                }
            }
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

            self.init_state();
        }
    }

    fn window_event(
        &mut self,
        event_loop: &winit::event_loop::ActiveEventLoop,
        _window_id: winit::window::WindowId,
        event: winit::event::WindowEvent,
    ) {
        let input_item: Option<()> = match event {
            WindowEvent::CloseRequested => {
                println!("Close requested, exiting application.");
                event_loop.exit();
                None
            }
            WindowEvent::Resized(physical_size) => {
                println!("Window resized to: {:?}", physical_size);
                None // will eventually cause window to update
            }

            WindowEvent::KeyboardInput {
                event: key_event, ..
            } => {
                self.input_handler.handle_keyboard(&key_event);
                Some(())
            }
            WindowEvent::MouseInput { button, state, .. } => {
                self.input_handler.handle_mouse(state, button);
                Some(())
            }
            WindowEvent::CursorMoved { position, .. } => {
                self.input_handler.handle_cursor(position);
                Some(())
            }

            _ => None,
        };
        if let Some(item) = input_item {
            match &self.api_state {
                ApiState::WgpuState { state } => {
                    // here state can be accessed specifically with the wgpu api
                }
            }
        }

        if let Some(window) = &self.window {
            window.request_redraw();
        }
    }
}
