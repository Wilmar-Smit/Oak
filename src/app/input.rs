use winit::{
    dpi::PhysicalPosition,
    event::{ElementState, KeyEvent, MouseButton, WindowEvent},
    window::Cursor,
};

pub struct InputHandler {
    cursorPosition: PhysicalPosition<f64>,
}

impl InputHandler {
    pub const fn new() -> Self {
        Self {
            cursorPosition: PhysicalPosition { x: 0.0, y: 0.0 },
        }
    }

    pub const fn handle_keyboard(&mut self, event: &KeyEvent) {
        /* keyboard events */
    }
    pub const fn handle_mouse(&mut self, state: ElementState, button: MouseButton) {
        // mouse clicks
    }
    pub const fn handle_cursor(&mut self, position: PhysicalPosition<f64>) {
        self.cursorPosition = position;
    }
}
