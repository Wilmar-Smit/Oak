#include "window.hpp"
#include <stdexcept>

Oak_Window::Oak_Window() {

  SDL_Init(SDL_INIT_VIDEO);

  this->window = SDL_CreateWindow("OAK", 640, 480, SDL_WINDOW_RESIZABLE);

  if (this->window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n",
                 SDL_GetError());
    throw std::runtime_error("Window could not be Created");
  }
}

void Oak_Window::start() {

  bool done = false;
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        done = true;
      }
      // game tree logic here
      // Followed by render logic
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}

Oak_Window::~Oak_Window() {
  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
}
