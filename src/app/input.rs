use winit::{
    dpi::PhysicalPosition,
    event::{ElementState, KeyEvent, MouseButton, WindowEvent},
    window::Cursor,
};

// will need to handle
pub struct InputHandler {
    cursorPosition: PhysicalPosition<f64>,
}

impl InputHandler {
    pub fn new() -> Self {
        Self {
            cursorPosition: PhysicalPosition { x: 0.0, y: 0.0 },
        }
    }

    pub fn handle_keyboard(self, event: &KeyEvent) { /* keyboard events */
    }
    pub fn handle_mouse(&mut self, state: ElementState, button: MouseButton) {
        // mouse clicks
    }
    pub fn handle_cursor(&mut self, position: PhysicalPosition<f64>) {
        self.cursorPosition = position;
    }
}
