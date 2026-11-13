# App (Api agnostic)

The `App` module manages the operating system window and event loop using `winit`.

It is strictly responsible for handling window-level actions like initialization, scaling, closing, and capturing raw user input (such as keyboard presses and mouse movements), passing those events along to the rest of the application without knowing anything about graphics or rendering.

# State (API specific)

The `State` module acts as the core coordinator for your application's data and GPU context.

It owns the fundamental `wgpu` plumbing—including the instance, surface, device, queue, and configuration—while also maintaining your active application state, loaded resources, buffers, and materials. It handles per-frame updates and orchestrates when drawing should occur.

# Renderer (API specific )

The `Renderer` module is exclusively responsible for executing GPU rendering commands and drawing logic.

It takes the data provided by `State`, creates command encoders, manages render passes, binds pipelines and shaders, and issues the final draw calls to render graphics onto the screen.
