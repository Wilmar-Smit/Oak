# Structure

- Code is provided, if code doesnt match provided consider it somewhat outdated

## Application.rs

### OakApp

```rs
pub struct OakApp {
    window: Option<Arc<Window>>,
    input_handler: InputHandler,
    state: ApiState,
}

impl OakApp {
    pub fn new(state: ApiState) -> Self {
        Self {
            window: None,
            input_handler: InputHandler::new(),
            state,
        }
    }
}
```

Initializes window,input_handler and state  
`window` is from winit

`input_handler` is a struct that returns an agnostic item that each api must be able to use.

`state` is an enum that will be initialized with the window by the application depending on the api passed through `main`, this requires a match to be done on the state in order to expose the api internals for the input however they should all take the same item anyway.

### window event

```rs
    fn window_event(
        &mut self,
        event_loop: &winit::event_loop::ActiveEventLoop,
        _window_id: winit::window::WindowId,
        event: winit::event::WindowEvent,
    ) {
```
